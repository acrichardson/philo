/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1234 <user1234@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:24:59 by user1234          #+#    #+#             */
/*   Updated: 2025/11/15 14:52:53 by user1234         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_ended(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data_ptr->mutex);
	result = philo->data_ptr->ended;
	pthread_mutex_unlock(&philo->data_ptr->mutex);
	return (result);
}

void	lock_left_right(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (has_ended(philo) == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	if (has_ended(philo) == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
}

void	lock_right_left(t_philo *philo)
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

int	check_ended(t_philo philo)
{
	pthread_mutex_lock(&philo.data_ptr->mutex);
	if (philo.data_ptr->ended)
	{
		pthread_mutex_unlock(&philo.data_ptr->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo.data_ptr->mutex);
	return (0);
}

void	safe_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->print_mutex);
	pthread_mutex_lock(&philo->data_ptr->mutex);
	if (!philo->data_ptr->ended)
	{
		printf("%ld %d %s\n", get_time_in_ms()
			- philo->data_ptr->st, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data_ptr->mutex);
	pthread_mutex_unlock(&philo->data_ptr->print_mutex);
}

// void	join_philos(t_data data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data.num_philos)
// 	{
// 		pthread_join(data.philos[i].thread, NULL);
// 		i++;
// 	}
// 	return ;
// }