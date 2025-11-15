/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1234 <user1234@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:23:21 by asrichar          #+#    #+#             */
/*   Updated: 2025/11/15 14:48:45 by user1234         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	long			st;
	pthread_t		monitor_thread;
	pthread_mutex_t	print_mutex;
	int				ended;
	int				iter;
	pthread_mutex_t	mutex;
	pthread_mutex_t	start_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data_ptr;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
}	t_philo;

int			init_data(t_data *data, char **argv);
void		*philo_routine(void *Phill);
long		get_time_in_ms(void);
void		safe_print(char *msg, t_philo *philo);
void		monitor_print(char *msg, t_philo *philo);
int			init_data(t_data *data, char **argv);
void		write_data_philos(t_data *data);
void		lock_left_right(t_philo *philo);
void		lock_right_left(t_philo *philo);
int			philo_eat_sleep_think(t_philo *philo);
void		*actual_routine(t_philo *philo);
void		smart_usleep(long duration_ms);
void		join_philos(t_data data);
int			check_args(int argc, char **argv);
int			is_digit(char c);
int			is_positive_number(char *str);
void		error_arguments(void);
long		get_time_in_ms(void);
void		safe_print(char *msg, t_philo *philo);
int			check_ended(t_philo philo);
int			malloc_check(pthread_t thread);

#endif