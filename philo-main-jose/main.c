/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asrichar <asrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:23:21 by asrichar          #+#    #+#             */
/*   Updated: 2025/11/13 20:49:25 by asrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  check_death(t_data *data)
{
    int     i;
    long    ct;
    
    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_lock(&data->philos[i].meal_mutex);
        ct = get_time_in_ms();
        if (ct - data->philos[i].last_meal_time > data->time_to_die)
        {
            pthread_mutex_lock(&data->mutex);
            // if (data->ended == 1)
            // {
            //     pthread_mutex_unlock(&data->mutex);
            //     pthread_mutex_unlock(&data->philos[i].meal_mutex);
            //     return (1);
            // }
            data->ended = 1;
            
            
            pthread_mutex_unlock(&data->mutex);
            
            monitor_print("died", &data->philos[i]);
            
            pthread_mutex_unlock(&data->philos[i].meal_mutex);
            return (1);
        }
        pthread_mutex_unlock(&data->philos[i].meal_mutex);
        i++;
    }
    return (0);
}

// hcange global shared ended naar personal philo dead en gebruik die mutex gewon veel minder...
// misschien houden ze de print lock te lang vast. check dat ook even
// vraag Noah wat hij denkt.

static int  check_completion(t_data *data)
{
    int done;
    int i;

    done = 0;
    i = 0;
    
    if (data->iter != -10)
    {
    while (i < data->num_philos)
    {
        pthread_mutex_lock(&data->philos[i].meal_mutex); // NEW
        if (data->philos[i].meals_eaten >= data->iter )
            done++;
        pthread_mutex_unlock(&data->philos[i].meal_mutex); // NEW
        i++;
    }
    
    pthread_mutex_lock(&data->mutex); // protect write
    if (done == data->num_philos)
    {
        //pthread_mutex_lock(&data->mutex);
        data->ended = 1;
        pthread_mutex_unlock(&data->mutex);
        return (1);
    }
    pthread_mutex_unlock(&data->mutex);
    }
    

    return (0);
}
void    *monitor_routine(void *void_data)
{
    t_data  *data;
    data = (t_data *)void_data;
    while (1)
    {
        // pthread_mutex_lock(&data->mutex);
        // if (data->ended)
        // {
        //     pthread_mutex_unlock(&data->mutex);
        //     break ;
        // }
        // pthread_mutex_unlock(&data->mutex);
        if (check_death(data) || check_completion(data))
        {
            
            break ;
        }
        usleep(500);
        // smart_usleep(1, data);
    }
    return (NULL);
}


int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int is_positive_number(char *str)
{
    int i = 0;
    if (!str || !str[0])
        return (0);
    while (str[i])
    {
        if (!is_digit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int check_args(int argc, char **argv)
{
    int i;

    if (argc < 5 || argc > 6)
        return (0);
    i = 1;
    while (i < argc)
    {
        if (!is_positive_number(argv[i]))
            return (0);
        i++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_data  data;

    if (!check_args(argc, argv))
    {
        write(2, "Error: invalid arguments\n", 25);
        return (1);
    }
    
    int     i;
    i = 0;
    if (argc < 5)
        return (1);
        
    if (init_data(&data, argv))
        return (1);
    write_data_philos(&data);
    if (data.num_philos == 1)
    {
        pthread_join(data.philos[0].thread, NULL);
        free(data.philos);
        free(data.forks);
        return (0);
    }
    pthread_create(&data.monitor_thread, NULL, monitor_routine, &data);
    //also in if statement?
    while (i < data.num_philos)
    {
        pthread_join(data.philos[i].thread, NULL);
        i++;
    }
    pthread_join(data.monitor_thread, NULL);
    free(data.philos);
    free(data.forks);
    return (0);
}