/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1234 <user1234@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:24:59 by user1234          #+#    #+#             */
/*   Updated: 2025/11/13 01:33:59 by user1234         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    lock_left_right(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    
    pthread_mutex_lock(&philo->data_ptr->mutex);
    if (philo->data_ptr->ended)
    {
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        pthread_mutex_unlock(philo->left_fork);
        return ;
    }
    pthread_mutex_unlock(&philo->data_ptr->mutex);
    
    pthread_mutex_lock(philo->right_fork);
    
    pthread_mutex_lock(&philo->data_ptr->mutex);
    if (philo->data_ptr->ended)
    {
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        return ;
    }
    pthread_mutex_unlock(&philo->data_ptr->mutex);
}

void    lock_right_left(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    
    pthread_mutex_lock(&philo->data_ptr->mutex);
    if (philo->data_ptr->ended)
    {
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        pthread_mutex_unlock(philo->right_fork);
        return ;
    }
    pthread_mutex_unlock(&philo->data_ptr->mutex);
    
    pthread_mutex_lock(philo->left_fork);
    
    pthread_mutex_lock(&philo->data_ptr->mutex);
    if (philo->data_ptr->ended)
    {
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return ;
    }
    pthread_mutex_unlock(&philo->data_ptr->mutex);
}

int philo_eat_sleep_think(t_philo *philo)
{
    pthread_mutex_lock(&philo->data_ptr->mutex);
    if (philo->data_ptr->ended)
    {
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data_ptr->mutex);

    safe_print("is eating", philo);
    smart_usleep(philo->data_ptr->time_to_eat, philo->data_ptr);

    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal_time = get_time_in_ms();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);

    pthread_mutex_lock(&philo->data_ptr->mutex);
    if (philo->data_ptr->ended)
    {
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data_ptr->mutex);

    safe_print("is sleeping", philo);
    smart_usleep(philo->data_ptr->time_to_sleep, philo->data_ptr);

    pthread_mutex_lock(&philo->data_ptr->mutex);
    if (philo->data_ptr->ended)
    {
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data_ptr->mutex);

    safe_print("is thinking", philo);
    
    if (philo->data_ptr->num_philos % 2 == 1)
    {
        usleep(1000);  // 1ms thinking delay
    }
    
    return (0);
}

void    *actual_routine(t_philo *philo)
{
    // int i = 0;
    
    while (1)
    {
        pthread_mutex_lock(&philo->data_ptr->mutex);
        if (philo->data_ptr->ended)
        {
            pthread_mutex_unlock(&philo->data_ptr->mutex);
            break ;
        }
        pthread_mutex_unlock(&philo->data_ptr->mutex);
        
        if (philo->id % 2 == 0)
            lock_left_right(philo);
        else
            lock_right_left(philo);
            
        if (philo_eat_sleep_think(philo))
            break ;
        // i++;
    }
    return (NULL);
}

void    *philo_routine(void *Phill)
{
    t_philo *philo = (t_philo *)Phill;
    
    pthread_mutex_lock(&philo->data_ptr->start_mutex);
    pthread_mutex_unlock(&philo->data_ptr->start_mutex);
    
    if (philo->id > 1)
        usleep(philo->id * 50);  // Max 200us delay for philosopher 4
    
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal_time = philo->data_ptr->st;
    pthread_mutex_unlock(&philo->meal_mutex);
    
    //     // ADD SMALL STAGGERED START BASED ON PHILOSOPHER ID
    // if (philo->id > 1)
    //     usleep(philo->id * 100);  // Later philosophers wait longer
        
    // BETTER STAGGERING - ODD PHILOS WAIT LONGER
    // if (philo->id % 2 == 0)
    //     usleep(50);  // Even philosophers wait 1ms
    // else if (philo->id == philo->data_ptr->num_philos)  // Last philosopher waits longer
    //     usleep(100);
    
    // SAFE STAGGERED START - Very small delays to prevent all philosophers
    // trying to grab forks at exactly the same time

    safe_print("started", philo);
    
    // MOVE THIS SOMEWHERE ELSE PLS
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

