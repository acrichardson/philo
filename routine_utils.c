/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1234 <user1234@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:24:59 by user1234          #+#    #+#             */
/*   Updated: 2025/11/08 13:17:08 by user1234         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    lock_left_right(t_philo *philo)
{
    pthread_mutex_lock(&philo->data_ptr->mutex);
    if (philo->data_ptr->ended)
    {
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        return ;
    }
    // if (philo->data_ptr->ended)
    // {
        //  pthread_mutex_unlock(philo->left_fork);
        //  return ;
        // }
    // // double check
    pthread_mutex_unlock(&philo->data_ptr->mutex);
    
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
}
void    lock_right_left(t_philo *philo)
{
    pthread_mutex_lock(&philo->data_ptr->mutex);
    if (philo->data_ptr->ended)
    {
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        return ;
    }
        // if (philo->data_ptr->ended)
        // {
            //  pthread_mutex_unlock(philo->right_fork);
            //  return ;
            // }
    // //  samesame check
    pthread_mutex_unlock(&philo->data_ptr->mutex);
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(philo->left_fork);
}
// int philo_eat_sleep_think(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->data_ptr->mutex);
//     // maak ff aparte functie
//     if (philo->data_ptr->ended)
//     {
//         pthread_mutex_unlock(&philo->data_ptr->mutex);
//         return (1);
//     }
//     // check
//     pthread_mutex_unlock(&philo->data_ptr->mutex);
    
//     // KANKER IK BLIJF SWITCHEN
//     safe_print("is eating", philo);
//     smart_usleep(philo->data_ptr->time_to_eat, philo->data_ptr);
    
//     pthread_mutex_lock(&philo->meal_mutex); //newnewnewnew
//     philo->last_meal_time = get_time_in_ms();
//     philo->meals_eaten++;
//     pthread_mutex_unlock(&philo->meal_mutex); //newnewenwwrappednow
    
    
//     pthread_mutex_unlock(philo->right_fork);
//     pthread_mutex_unlock(philo->left_fork);
    
//     // if (philo->data_ptr->ended)
//     //  return (1);
//     safe_print("is sleeping", philo);
//     smart_usleep(philo->data_ptr->time_to_sleep, philo->data_ptr);
//     // if (philo->data_ptr->ended)
//     //  return (1);
//     safe_print("is thinking", philo);
//     return (0);
// }

int philo_eat_sleep_think(t_philo *philo)
{
    pthread_mutex_lock(&philo->data_ptr->mutex);
    if (philo->data_ptr->ended)
    {
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data_ptr->mutex);

    // Take forks first (already done outside)
    safe_print("is eating", philo);

    // FUNCTIONAL CHANGE: sleep first, then update last_meal_time
    smart_usleep(philo->data_ptr->time_to_eat, philo->data_ptr);

    // FUNCTIONAL CHANGE: Update last_meal_time AFTER eating
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal_time = get_time_in_ms();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);

    safe_print("is sleeping", philo);
    smart_usleep(philo->data_ptr->time_to_sleep, philo->data_ptr);
    safe_print("is thinking", philo);

    return (0);
}

void    *actual_routine(t_philo *philo)
{
    int i;
    i = 0;
    pthread_mutex_lock(&philo->data_ptr->mutex);
    while ((!philo->data_ptr->ended && i < philo->data_ptr->iter)
        || (!philo->data_ptr->ended && philo->data_ptr->iter == -10))
    {
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        if (philo->id % 2 == 0)
            lock_left_right(philo);
        else
            lock_right_left(philo);
        if (philo_eat_sleep_think(philo))
        {
            pthread_mutex_lock(&philo->data_ptr->mutex);
            break ;
        }
        i++;
        pthread_mutex_lock(&philo->data_ptr->mutex);
    }
    pthread_mutex_unlock(&philo->data_ptr->mutex);
    return (NULL);
}
void    *philo_routine(void *Phill)
{
    t_philo *philo;
    philo = (t_philo *)Phill;
    safe_print("started", philo);
    if (philo->data_ptr->num_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        safe_print("took the left fork", philo);
        usleep(philo->data_ptr->time_to_die * 1000);
        safe_print("died", philo);
        pthread_mutex_unlock(philo->left_fork);
        return (NULL);
    }
    actual_routine(philo);
    return (NULL);
}