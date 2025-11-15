/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1234 <user1234@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:23:21 by asrichar          #+#    #+#             */
/*   Updated: 2025/11/15 14:56:36 by user1234         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	check_death(t_data *data)
{
	int		i;
	long	ct;
	long	last_meal;
	long	time_since_meal;

	ct = get_time_in_ms();
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		last_meal = data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		time_since_meal = ct - last_meal;
		if (time_since_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->mutex);
			data->ended = 1;
			pthread_mutex_unlock(&data->mutex);
			monitor_print("died", &data->philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static	int	check_completion(t_data *data)
{
	int	done;
	int	i;

	done = 0;
	i = 0;
	if (data->iter != -10)
	{
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			if (data->philos[i].meals_eaten >= data->iter)
				done++;
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			i++;
		}
		pthread_mutex_lock(&data->mutex);
		if (done == data->num_philos)
		{
			data->ended = 1;
			pthread_mutex_unlock(&data->mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->mutex);
	}
	return (0);
}

void	*monitor_routine(void *void_data)
{
	t_data	*data;

	data = (t_data *)void_data;
	while (1)
	{
		if (check_death(data) || check_completion(data))
		{
			break ;
		}
		usleep(500);
	}
	return (NULL);
}

void	join_free(pthread_t thread, t_data data)
{
	pthread_join(thread, NULL);
	free(data.philos);
	free(data.forks);
	return ;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(argc, argv))
	{
		write(2, "Error: invalid arguments\n", 25);
		return (1);
	}
	if (argc < 5 || atoi(argv[1]) < 1)
		return (0);
	if (init_data(&data, argv))
		return (1);
	write_data_philos(&data);
	if (data.num_philos == 1)
	{
		join_free(data.philos[0].thread, data);
		return (0);
	}
	pthread_create(&data.monitor_thread, NULL, monitor_routine, &data);
	join_philos(data);
	join_free(data.monitor_thread, data);
	return (0);
}
