/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1234 <user1234@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:08:52 by user1234          #+#    #+#             */
/*   Updated: 2025/11/13 01:34:42 by user1234         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_time_in_ms(void)
{
    struct timeval  ct;
    long            milliseconds;
    gettimeofday(&ct, NULL);
    milliseconds = ct.tv_sec * 1000;
    milliseconds += ct.tv_usec / 1000;
    return (milliseconds);
}
// void    safe_print(char *msg, t_philo *philo)
// {
    
//     // printf("\nphilo->data_ptr->ended = %i\n", philo->data_ptr->ended);
//     pthread_mutex_lock(&philo->data_ptr->print_mutex);
//     // pthread_mutex_lock(&philo->meal_mutex);
//     pthread_mutex_lock(&philo->data_ptr->mutex);
//     if (philo->data_ptr->ended != 1
//         // && philo->data_ptr->iter < philo->meals_eaten
//     )
//     {
//         // pthread_mutex_lock(&philo->data_ptr->print_mutex);
//         //check of ie leeft hier
//             // of iets anders returnen?
//         printf("%ld %d %s\n", get_time_in_ms()
//             - philo->data_ptr->st, philo->id, msg);
//         pthread_mutex_unlock(&philo->data_ptr->mutex);
//         pthread_mutex_unlock(&philo->data_ptr->print_mutex);
//         // pthread_mutex_unlock(&philo->meal_mutex);
//         return ;
//     }
//     pthread_mutex_unlock(&philo->data_ptr->mutex);
//     pthread_mutex_unlock(&philo->data_ptr->print_mutex);
//     // pthread_mutex_unlock(&philo->meal_mutex);
// }

void safe_print(char *msg, t_philo *philo)
{
    pthread_mutex_lock(&philo->data_ptr->print_mutex);  // prevent overlapping prints

    // pthread_mutex_lock(&philo->data_ptr->mutex);  // check if simulation ended
    // if (philo->data_ptr->ended)
    // {
    //     pthread_mutex_unlock(&philo->data_ptr->mutex);
    //     pthread_mutex_unlock(&philo->data_ptr->print_mutex);
    //     return;  // do not print anything if a philosopher already died
    // }
    // pthread_mutex_unlock(&philo->data_ptr->mutex);

    // now safe to print
    printf("%ld %d %s\n", get_time_in_ms() - philo->data_ptr->st, philo->id, msg);

    pthread_mutex_unlock(&philo->data_ptr->print_mutex);
}

// //MINE
// int init_data(t_data *data, char **argv)
// {
//     int i;
//     data->num_philos = atoi(argv[1]);
//     data->time_to_die = atoi(argv[2]);
//     data->time_to_eat = atoi(argv[3]);
//     data->time_to_sleep = atoi(argv[4]);
//     data->philos = malloc(sizeof(t_philo) * data->num_philos);
//     data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
//     // NULL checks doen nog!
//     data->st = get_time_in_ms();
//     data->ended = 0;
//     if (argv[5])
//         data->iter = atoi(argv[5]);
//     else
//         data->iter = -10;
//     pthread_mutex_init(&data->print_mutex, NULL);
//     // ook check for fail goed = 0
//     pthread_mutex_init(&data->mutex, NULL);
//     i = 0;
//     while (i < data->num_philos)
//     {
//         pthread_mutex_init(&data->forks[i], NULL);
//         i++;
//     }
//     pthread_mutex_init(&data->start_mutex, NULL);
//     pthread_mutex_lock(&data->start_mutex);
//     return (0);
// }

int init_data(t_data *data, char **argv)
{
    int i;
    data->num_philos = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    // NULL checks doen nog!
    data->st = get_time_in_ms();
    data->ended = 0;
    if (argv[5])
        data->iter = atoi(argv[5]);
    else
        data->iter = -10;
    pthread_mutex_init(&data->print_mutex, NULL);
    // ook check for fail goed = 0
    pthread_mutex_init(&data->mutex, NULL);
    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->start_mutex, NULL);
    pthread_mutex_lock(&data->start_mutex);  // LOCK INITIALLY
    return (0);
}

// void    write_data_philos(t_data *data)
// {
//     int i;
//     i = 0;
//     while (i < data->num_philos)
//     {
//         data->philos[i].id = i + 1;
//         data->philos[i].data_ptr = data;
//         // data->philos[i].last_meal_time = 0;
//         data->philos[i].last_meal_time = data->st;
//         data->philos[i].left_fork = &data->forks[i];
//         data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
//         data->philos[i].meals_eaten = 0;
//         pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
//         if (pthread_create(&data->philos[i].thread, NULL,
//             philo_routine, &data->philos[i]) != 0)
//             {
//                 // cant return cause void? keep?
//                 // return specific value that can be used in mother function that can then take action?
//             }
//             // check everywhere if failed
//         i++;
//     }
//     // START ALL PHILOSOPHERS SAME TIME
//     usleep(1000);  // Ensure all threads are waiting
//     data->st = get_time_in_ms();
//     pthread_mutex_unlock(&data->start_mutex);  // RELEASE ALL THREADS
// }

void    write_data_philos(t_data *data)
{
    int i = 0;
    while (i < data->num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].data_ptr = data;
        data->philos[i].last_meal_time = 0;  // Should be 0 initially
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        data->philos[i].meals_eaten = 0;
        pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
        pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
        i++;
    }
    
    // Wait for ALL threads to be ready before starting
    usleep(5000);  // Increased from 1000 to 5000 for better synchronization
    
    long start_time = get_time_in_ms();
    data->st = start_time;
    
    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_lock(&data->philos[i].meal_mutex);
        data->philos[i].last_meal_time = start_time;  // Set to actual start time
        pthread_mutex_unlock(&data->philos[i].meal_mutex);
        i++;
    }
    
    pthread_mutex_unlock(&data->start_mutex);
}

void    smart_usleep(long duration_ms, t_data *data)
{
    long    start;
    start = get_time_in_ms();
    while (1)
    {
        pthread_mutex_lock(&data->mutex);
        if (data->ended)
        {
            pthread_mutex_unlock(&data->mutex);
            break ;
        }
        pthread_mutex_unlock(&data->mutex);
        // misschien while loopje van maken
        if (get_time_in_ms() - start >= duration_ms)
            break ;
        usleep(10);
    }
}
