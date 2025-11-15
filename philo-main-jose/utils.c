/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1234 <user1234@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:08:52 by user1234          #+#    #+#             */
/*   Updated: 2025/11/15 14:55:02 by user1234         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->print_mutex);
	printf("%ld %d %s\n", get_time_in_ms()
		- philo->data_ptr->st, philo->id, msg);
	pthread_mutex_unlock(&philo->data_ptr->print_mutex);
}

// int	malloc_check(pthread_t thread)
// {
// 	if (!thread)
// 		return (1);
// 	return (0);
// }

// static int	init_mutexes(t_data *data)
// {
// 	int	i;

// 	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
// 		return (1);
// 	if (pthread_mutex_init(&data->mutex, NULL) != 0)
// 		return (1);
// 	if (pthread_mutex_init(&data->start_mutex, NULL) != 0)
// 		return (1);
// 	i = 0;
// 	while (i < data->num_philos)
// 	{
// 		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
// 			return (1);
// 		i++;
// 	}
// 	pthread_mutex_lock(&data->start_mutex);
// 	return (0);
// }

// static int	allocate_resources(t_data *data)
// {
// 	data->philos = malloc(sizeof(t_philo) * data->num_philos);
// 	if (!data->philos)
// 		return (1);
// 	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
// 	if (!data->forks)
// 	{
// 		free(data->philos);
// 		return (1);
// 	}
// 	return (0);
// }

// int	init_data(t_data *data, char **argv)
// {
// 	data->num_philos = atoi(argv[1]);
// 	data->time_to_die = atoi(argv[2]);
// 	data->time_to_eat = atoi(argv[3]);
// 	data->time_to_sleep = atoi(argv[4]);
// 	if (allocate_resources(data) != 0)
// 		return (1);
// 	data->ended = 0;
// 	if (argv[5])
// 		data->iter = atoi(argv[5]);
// 	else
// 		data->iter = -10;
// 	if (init_mutexes(data) != 0)
// 	{
// 		free(data->philos);
// 		free(data->forks);
// 		return (1);
// 	}
// 	return (0);
// }

// void	write_data_philos(t_data *data)
// {
// 	int		i;

// 	i = 0;
// 	while (i < data->num_philos)
// 	{
// 		data->philos[i].id = i + 1;
// 		data->philos[i].data_ptr = data;
// 		data->philos[i].left_fork = &data->forks[i];
// 		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
// 		data->philos[i].meals_eaten = 0;
// 		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
// 		pthread_create(&data->philos[i].thread, NULL,
// 			philo_routine, &data->philos[i]);
// 		i++;
// 	}
// 	data->st = get_time_in_ms();
// 	i = 0;
// 	while (i < data->num_philos)
// 	{
// 		pthread_mutex_lock(&data->philos[i].meal_mutex);
// 		data->philos[i].last_meal_time = data->st;
// 		pthread_mutex_unlock(&data->philos[i].meal_mutex);
// 		i++;
// 	}
// 	pthread_mutex_unlock(&data->start_mutex);
// }

void	smart_usleep(long duration_ms)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time_in_ms();
	while (1)
	{
		elapsed = get_time_in_ms() - start;
		if (elapsed >= duration_ms)
			break ;
		remaining = duration_ms - elapsed;
		if (remaining > 1)
			usleep(1000);
		else
			usleep(remaining * 1000);
	}
}

long	get_time_in_ms(void)
{
	struct timeval	ct;
	long			milliseconds;

	gettimeofday(&ct, NULL);
	milliseconds = ct.tv_sec * 1000;
	milliseconds += ct.tv_usec / 1000;
	return (milliseconds);
}
