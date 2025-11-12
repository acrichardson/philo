#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
#include <stdbool.h>

typedef struct s_philo  t_philo;
typedef struct s_data
{
    int             num_philos;
    t_philo         *philos;
    pthread_mutex_t *forks;
    int             time_to_eat;
    int             time_to_sleep;
    int             time_to_die;
    long            st;
    pthread_t       monitor_thread;
    pthread_mutex_t print_mutex;
    int             ended;
    int             iter;
    pthread_mutex_t mutex;
    // NEW — used to protect `ended`
}   t_data;
typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data          *data_ptr;
    long            last_meal_time;
    int             meals_eaten;
    pthread_mutex_t meal_mutex;
    //  NEW — protects last_meal_time + meals_eaten
}   t_philo;
int     init_data(t_data *data, char **argv);
void    *philo_routine(void *Phill);
long    get_time_in_ms(void);
void    safe_print(char *msg, t_philo *philo);
int     init_data(t_data *data, char **argv);
void    write_data_philos(t_data *data);
void    lock_left_right(t_philo *philo);
void    lock_right_left(t_philo *philo);
int     philo_eat_sleep_think(t_philo *philo);
void    *actual_routine(t_philo *philo);
// void *philo_routine(void *Phill);
void    smart_usleep(long duration_ms, t_data *data);
#endif