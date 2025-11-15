/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1234 <user1234@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:08:52 by user1234          #+#    #+#             */
/*   Updated: 2025/11/15 14:56:06 by user1234         ###   ########.fr       */
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
