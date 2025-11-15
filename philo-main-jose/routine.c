/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1234 <user1234@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:32:59 by user1234          #+#    #+#             */
/*   Updated: 2025/11/15 14:51:08 by user1234         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat_sleep_think(t_philo *philo)
{
	if (check_ended(*philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print("is eating", philo);
	smart_usleep(philo->data_ptr->time_to_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (check_ended(*philo) == 1)
		return (1);
	safe_print("is sleeping", philo);
	smart_usleep(philo->data_ptr->time_to_sleep);
	if (check_ended(*philo) == 1)
		return (1);
	safe_print("is thinking", philo);
	if ((philo->data_ptr->num_philos % 2) == 1)
	{
		usleep(1000);
	}
	return (0);
}

void	*actual_routine(t_philo *philo)
{
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
	}
	return (NULL);
}

void	*philo_routine(void *Phill)
{
	t_philo	*philo;

	philo = (t_philo *)Phill;
	pthread_mutex_lock(&philo->data_ptr->start_mutex);
	pthread_mutex_unlock(&philo->data_ptr->start_mutex);
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
