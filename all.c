// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   all.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: user1234 <user1234@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/27 16:23:21 by asrichar          #+#    #+#             */
// /*   Updated: 2025/11/08 10:20:20 by user1234         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// static int  check_death(t_data *data)
// {
//     int     i;
//     long    ct;
//     i = 0;
//     ct = get_time_in_ms();
//     while (i < data->num_philos)
//     {
//         pthread_mutex_lock(&data->philos[i].meal_mutex); // NEW
//         // dit eruit halen als ik kies om niet start tijd 0 te doen..
//         if (data->philos[i].meals_eaten < data->iter
//             && ct - data->philos[i].last_meal_time > data->time_to_die)
//         {
//             pthread_mutex_lock(&data->mutex);
//             if(data->ended == 1)
//             {
//                 pthread_mutex_lock(&data->mutex);
//                 return (1);
//             }
//             pthread_mutex_unlock(&data->mutex);
//                 //1?
//             safe_print("died in check death", &data->philos[i]);
//             // printf("%ld %i MIAAAAAUWdied\n", ct - data->st, data->philos[i].id);
//             pthread_mutex_unlock(&data->philos[i].meal_mutex); // NEW
//             // pthread_mutex_lock(&data->mutex); // protect write
//             // data->ended = 1;
//             // pthread_mutex_unlock(&data->mutex);
//             pthread_mutex_lock(&data->mutex); // protect write
//             data->ended = 1;
//             pthread_mutex_unlock(&data->mutex);
//             return (1);
//         }
//         pthread_mutex_unlock(&data->philos[i].meal_mutex); // NEW
//         i++;
//     }
//     return (0);
// }
// static int  check_completion(t_data *data)
// {
//     int done;
//     int i;
//     if (data->iter <= 0)
//         return (0);
//     done = 0;
//     i = 0;
//     while (i < data->num_philos)
//     {
//         pthread_mutex_lock(&data->philos[i].meal_mutex); // NEW
//         if (data->philos[i].meals_eaten >= data->iter)
//             done++;
//         pthread_mutex_unlock(&data->philos[i].meal_mutex); // NEW
//         i++;
//     }
    
//     pthread_mutex_lock(&data->mutex); // protect write
//     if (done == data->num_philos)
//     {
//         //pthread_mutex_lock(&data->mutex);
//         data->ended = 1;
//         pthread_mutex_unlock(&data->mutex);
//         return (1);
//     }
//     pthread_mutex_unlock(&data->mutex);
//     return (0);
// }
// void    *monitor_routine(void *void_data)
// {
//     t_data  *data;
//     data = (t_data *)void_data;
//     while (1)
//     {
//         pthread_mutex_lock(&data->mutex);
//         if (data->ended)
//         {
//             pthread_mutex_unlock(&data->mutex);
//             break ;
//         }
//         pthread_mutex_unlock(&data->mutex);
//         if (check_death(data) || check_completion(data))
//             break ;
//         smart_usleep(1000, data);
//     }
//     return (NULL);
// }
// int main(int argc, char **argv)
// {
//     t_data  data;
//     int     i;
//     i = 0;
//     if (argc < 5)
//         return (1);
//     if (init_data(&data, argv))
//         return (1);
//     write_data_philos(&data);
//     if (data.num_philos == 1)
//     {
//         // case_are_you_dumb(&data);
//         pthread_join(data.philos[0].thread, NULL);
//         free(data.philos);
//         free(data.forks);
//         return (0);
//     }
//     pthread_create(&data.monitor_thread, NULL, monitor_routine, &data);
//     //also in if statement?
//     while (i < data.num_philos)
//     {
//         pthread_join(data.philos[i].thread, NULL);
//         i++;
//     }
//     pthread_join(data.monitor_thread, NULL);
//     free(data.philos);
//     free(data.forks);
//     return (0);
// }
// 5:02
// NAME = philo
// SRCS =  main.c\
//         utils.c\
//         routine_utils.c\
// OBJS = $(SRCS:.c=.o)
// CC = cc
// CFLAGS = -Wall -Wextra -Werror \
// -fsanitize=thread -g
// all: $(NAME)
// $(NAME): $(OBJS)
//     $(CC) $(CFLAGS) $(OBJS) -o $(NAME)
// clean:
//     rm -f $(OBJS)
// fclean: clean
//     rm -f $(NAME)
// re: fclean all
// .PHONY: all clean fclean re
// 5:02
// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   philo.h                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: asrichar <asrichar@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/27 16:22:55 by asrichar          #+#    #+#             */
// /*   Updated: 2025/11/04 21:40:33 by asrichar         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
// // #ifndef PHILO_H
// // # define PHILO_H
// // # include <pthread.h>
// // # include <stdio.h>
// // # include <stdlib.h>
// // # include <unistd.h>
// // # include <sys/time.h>
// // #include <stdbool.h>
// // typedef struct s_philo  t_philo;
// // typedef struct s_data
// // {
// //     int             num_philos;
// //     t_philo         *philos;
// //     pthread_mutex_t *forks;
// //     int             time_to_eat;
// //     int             time_to_sleep;
// //     int             time_to_die;
// //     long            st;
// //     pthread_t       monitor_thread;
// //     pthread_mutex_t print_mutex;
// //     int             ended;
// //     int             iter;
// //     pthread_mutex_t mutex;
// //     // NEW — used to protect `ended`
// // }   t_data;
// // typedef struct s_philo
// // {
// //     int             id;
// //     pthread_t       thread;
// //     pthread_mutex_t *left_fork;
// //     pthread_mutex_t *right_fork;
// //     t_data          *data_ptr;
// //     long            last_meal_time;
// //     int             meals_eaten;
// //     pthread_mutex_t meal_mutex;
// //     //  NEW — protects last_meal_time + meals_eaten
// // }   t_philo;
// // int     init_data(t_data *data, char **argv);
// // void    *philo_routine(void *Phill);
// // long    get_time_in_ms(void);
// // void    safe_print(char *msg, t_philo *philo);
// // int     init_data(t_data *data, char **argv);
// // void    write_data_philos(t_data *data);
// // void    lock_left_right(t_philo *philo);
// // void    lock_right_left(t_philo *philo);
// // int     philo_eat_sleep_think(t_philo *philo);
// // void    *actual_routine(t_philo *philo);
// // // void *philo_routine(void *Phill);
// // void    smart_usleep(long duration_ms, t_data *data);
// // #endif
// 5:02
// https://github.com/soepgroente/philosophers
// 5:03
// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   routine_utils.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: asrichar <asrichar@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/29 12:24:59 by user1234          #+#    #+#             */
// /*   Updated: 2025/11/05 19:07:13 by asrichar         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
// #include "philo.h"
// #include "philo.h"
// void    lock_left_right(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->data_ptr->mutex);
//     if (philo->data_ptr->ended)
//     {
//         pthread_mutex_unlock(&philo->data_ptr->mutex);
//         return ;
//     }
//     // if (philo->data_ptr->ended)
//     // {
//         //  pthread_mutex_unlock(philo->left_fork);
//         //  return ;
//         // }
//     // // double check
//     pthread_mutex_unlock(&philo->data_ptr->mutex);
    
//     pthread_mutex_lock(philo->left_fork);
//     pthread_mutex_lock(philo->right_fork);
// }
// void    lock_right_left(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->data_ptr->mutex);
//     if (philo->data_ptr->ended)
//     {
//         pthread_mutex_unlock(&philo->data_ptr->mutex);
//         return ;
//     }
//         // if (philo->data_ptr->ended)
//         // {
//             //  pthread_mutex_unlock(philo->right_fork);
//             //  return ;
//             // }
//     // //  samesame check
//     pthread_mutex_unlock(&philo->data_ptr->mutex);
//     pthread_mutex_lock(philo->right_fork);
//     pthread_mutex_lock(philo->left_fork);
// }
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
//     // if (check_is_alive(...) == false)
//     // {
//     //  return ;
//     // }
    
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
// void    *actual_routine(t_philo *philo)
// {
//     int i;
//     i = 0;
//     pthread_mutex_lock(&philo->data_ptr->mutex);
//     while ((!philo->data_ptr->ended && i < philo->data_ptr->iter)
//         || (!philo->data_ptr->ended && philo->data_ptr->iter == 0))
//     {
//         pthread_mutex_unlock(&philo->data_ptr->mutex);
//         if (philo->id % 2 == 0)
//             lock_left_right(philo);
//         else
//             lock_right_left(philo);
//         if (philo_eat_sleep_think(philo))
//         {
//             pthread_mutex_lock(&philo->data_ptr->mutex);
//             break ;
//         }
//         i++;
//         pthread_mutex_lock(&philo->data_ptr->mutex);
//     }
//     pthread_mutex_unlock(&philo->data_ptr->mutex);
//     return (NULL);
// }
// void    *philo_routine(void *Phill)
// {
//     t_philo *philo;
//     philo = (t_philo *)Phill;
//     safe_print("started", philo);
//     if (philo->data_ptr->num_philos == 1)
//     {
//         pthread_mutex_lock(philo->left_fork);
//         safe_print("took the left fork", philo);
//         usleep(philo->data_ptr->time_to_die * 1000);
//         safe_print("died", philo);
//         pthread_mutex_unlock(philo->left_fork);
//         return (NULL);
//     }
//     actual_routine(philo);
//     return (NULL);
// }
// 5:03
// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   utils.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: asrichar <asrichar@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/29 12:08:52 by user1234          #+#    #+#             */
// /*   Updated: 2025/11/05 17:56:46 by asrichar         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
// #include "philo.h"
// long    get_time_in_ms(void)
// {
//     struct timeval  ct;
//     long            milliseconds;
//     gettimeofday(&ct, NULL);
//     milliseconds = ct.tv_sec * 1000;
//     milliseconds += ct.tv_usec / 1000;
//     return (milliseconds);
// }
// void    safe_print(char *msg, t_philo *philo)
// {
//     // printf("\nphilo->data_ptr->ended = %i\n", philo->data_ptr->ended);
//     if (philo->data_ptr->ended != 1
//         // && philo->data_ptr->iter < philo->meals_eaten
//     )
//     {
//         pthread_mutex_lock(&philo->data_ptr->print_mutex);
//         //check of ie leeft hier
//             // of iets anders returnen?
//         printf("%ld %d %s\n", get_time_in_ms()
//             - philo->data_ptr->st, philo->id, msg);
//         pthread_mutex_unlock(&philo->data_ptr->print_mutex);
//     }
// }
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
//         data->iter = 0;
//     pthread_mutex_init(&data->print_mutex, NULL);
//     // ook check for fail goed = 0
//     pthread_mutex_init(&data->mutex, NULL);
//     i = 0;
//     while (i < data->num_philos)
//     {
//         pthread_mutex_init(&data->forks[i], NULL);
//         i++;
//     }
//     return (0);
// }
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
// }
// // void smart_usleep(long duration_ms, t_data *data)
// // {
// //  long    start;
// //  start = get_time_in_ms();
// //  while (!data->ended
// //      && get_time_in_ms() - start < duration_ms)
// //      usleep(500);
// // }
// // check deze nog
// void    smart_usleep(long duration_ms, t_data *data)
// {
//     long    start;
//     start = get_time_in_ms();
//     while (1)
//     {
//         pthread_mutex_lock(&data->mutex); // NEW — safe read of `ended`
//         if (data->ended)
//         {
//             pthread_mutex_unlock(&data->mutex);
//             break ;
//         }
//         pthread_mutex_unlock(&data->mutex);
//         // misschien while loopje van maken
//         if (get_time_in_ms() - start >= duration_ms)
//             break ;
//         usleep(500);
//     }
// }
// 5:03
// failing:
// ./philo 5 800 200 200 7
// sometimes death, also thhinking after death:
// ended check before all prints/ IN the safe print!!!
// FIXED..
// ./philo 4 310 200 200
// noone dies.... it says one should die and quick...
// meeste van deze gefiixt
// ./philo 1 800 200 200
// // data races x 5?
// ./philo 5 800 200 200 7
// // dies instead of just exiting after 7 rounds
// ./philo 4 310 200 200
// // one should die quickly, noone dies....
// ./philo 1 800 200 200
// // data races x 5?
// ./philo 5 800 200 200 7
// // dies instead of just exiting after 7 rounds
// 3603 4 is sleeping
// 3626 2 is thinking
// 3803 4 is thinking
// 4011 1 died
// LLVMSymbolizer: error reading file: No such file or directory
// ==================
// WARNING: ThreadSanitizer: data race (pid=119422)
//   Write of size 4 at 0x7fff3c0a4920 by thread T6 (mutexes: write M1):
//     #0 check_death /home/asrichar/Code/Cycle_03/pipex_failed/main.c:32:16 (philo+0x4b9d9d)
//     #1 monitor_routine /home/asrichar/Code/Cycle_03/pipex_failed/main.c:85:7 (philo+0x4b9b48)
//   Previous read of size 4 at 0x7fff3c0a4920 by thread T2:
//     #0 actual_routine /home/asrichar/Code/Cycle_03/pipex_failed/routine_utils.c:95:28 (philo+0x4bafd9)
//     #1 philo_routine /home/asrichar/Code/Cycle_03/pipex_failed/routine_utils.c:124:2 (philo+0x4bb234)
//   As if synchronized via sleep:
//     #0 usleep <null> (philo+0x4473b6)
//     #1 smart_usleep /home/asrichar/Code/Cycle_03/pipex_failed/utils.c:108:3 (philo+0x4baaae)
//     #2 monitor_routine /home/asrichar/Code/Cycle_03/pipex_failed/main.c:87:3 (philo+0x4b9b76)
//   Location is stack of main thread.
//   Location is global '??' at 0x7fff3c085000 ([stack]+0x00000001f920)
//   Mutex M1 (0x7fff3c0a4928) created at:
//     #0 pthread_mutex_init <null> (philo+0x44b47d)
//     #1 init_data /home/asrichar/Code/Cycle_03/pipex_failed/utils.c:51:2 (philo+0x4ba63d)
//     #2 main /home/asrichar/Code/Cycle_03/pipex_failed/main.c:107:6 (philo+0x4ba0fb)
//   Thread T6 (tid=119429, running) created by main thread at:
//     #0 pthread_create <null> (philo+0x449c4b)
//     #1 main /home/asrichar/Code/Cycle_03/pipex_failed/main.c:115:2 (philo+0x4ba166)
//   Thread T2 (tid=119425, finished) created by main thread at:
//     #0 pthread_create <null> (philo+0x449c4b)
//     #1 write_data_philos /home/asrichar/Code/Cycle_03/pipex_failed/utils.c:75:3 (philo+0x4ba9f2)
//     #2 main /home/asrichar/Code/Cycle_03/pipex_failed/main.c:109:2 (philo+0x4ba11c)
// SUMMARY: ThreadSanitizer: data race /home/asrichar/Code/Cycle_03/pipex_failed/main.c:32:16 in check_death
// ==================
// ThreadSanitizer: reported 1 warnings
// ./philo 3 600 200 200
// // ze moete allen overleven. one dies EN het runt nog door.... wel elke x hetzelfde
// 1803 3 is thinking
// 1803 3 is eating
// 1803 2 is sleeping
// 2003 2 is thinking
// 2003 3 is sleeping
// 2003 1 is eating
// 2007 1 died
// 2007 1 is sleeping
// 2007 1 is thinking
// 2007 3 is thinking
// ./philo 200 800 200 200
// // gaat dood... loopt dan door. loopt dan vast...
// 3653 103 is sleeping
// 3654 104 is eating
// 3654 152 is thinking
// 3654 5 died
// 3654 105 is thinking
// LLVMSymbolizer: error reading file: No such file or directory
// ==================
// WARNING: ThreadSanitizer: data race (pid=126706)
//   Write of size 4 at 0x7ffda0a64520 by thread T201 (mutexes: write M1):
//     #0 check_death /home/asrichar/Code/Cycle_03/pipex_failed/main.c:32:16 (philo+0x4b9d9d)
//     #1 monitor_routine /home/asrichar/Code/Cycle_03/pipex_failed/main.c:85:7 (philo+0x4b9b48)
//   Previous read of size 4 at 0x7ffda0a64520 by thread T105:
//     #0 actual_routine /home/asrichar/Code/Cycle_03/pipex_failed/routine_utils.c:95:28 (philo+0x4bafd9)
//     #1 philo_routine /home/asrichar/Code/Cycle_03/pipex_failed/routine_utils.c:124:2 (philo+0x4bb234)
//   Location is stack of main thread.
//   Location is global '??' at 0x7ffda0a45000 ([stack]+0x00000001f520)
//   Mutex M1 (0x7ffda0a64528) created at:
//     #0 pthread_mutex_init <null> (philo+0x44b47d)
//     #1 init_data /home/asrichar/Code/Cycle_03/pipex_failed/utils.c:51:2 (philo+0x4ba63d)
//     #2 main /home/asrichar/Code/Cycle_03/pipex_failed/main.c:107:6 (philo+0x4ba0fb)
//   Thread T201 (tid=126940, running) created by main thread at:
//     #0 pthread_create <null> (philo+0x449c4b)
//     #1 main /home/asrichar/Code/Cycle_03/pipex_failed/main.c:115:2 (philo+0x4ba166)
//   Thread T105 (tid=126812, running) created by main thread at:
//     #0 pthread_create <null> (philo+0x449c4b)
//     #1 write_data_philos /home/asrichar/Code/Cycle_03/pipex_failed/utils.c:75:3 (philo+0x4ba9f2)
//     #2 main /home/asrichar/Code/Cycle_03/pipex_failed/main.c:109:2 (philo+0x4ba11c)
// SUMMARY: ThreadSanitizer: data race /home/asrichar/Code/Cycle_03/pipex_failed/main.c:32:16 in check_death
// ==================
// 4372 108 is thinking
// 4372 85 is sleeping
// 4373 114 is thinking
// 4373 83 is sleeping
// ./philo 5 800 200 200 1
// // moet stoppen na 1 ronde.. stopt maar gaat ook door aan einde + race
// 603 5 is thinking
// 605 2 is thinking
// 803 4 is thinking
// 1008 1 died
// LLVMSymbolizer: error reading file: No such file or directory
// ==================
// WARNING: ThreadSanitizer: data race (pid=127625)
//   Write of size 4 at 0x7ffeda870b60 by thread T6 (mutexes: write M1):
//     #0 check_death /home/asrichar/Code/Cycle_03/pipex_failed/main.c:32:16 (philo+0x4b9d9d)
//     #1 monitor_routine /home/asrichar/Code/Cycle_03/pipex_failed/main.c:85:7 (philo+0x4b9b48)
//   Previous read of size 4 at 0x7ffeda870b60 by thread T4:
//     #0 actual_routine /home/asrichar/Code/Cycle_03/pipex_failed/routine_utils.c:95:28 (philo+0x4bafd9)
//     #1 philo_routine /home/asrichar/Code/Cycle_03/pipex_failed/routine_utils.c:124:2 (philo+0x4bb234)
//   As if synchronized via sleep:
//     #0 usleep <null> (philo+0x4473b6)
//     #1 smart_usleep /home/asrichar/Code/Cycle_03/pipex_failed/utils.c:108:3 (philo+0x4baaae)
//     #2 monitor_routine /home/asrichar/Code/Cycle_03/pipex_failed/main.c:87:3 (philo+0x4b9b76)
//   Location is stack of main thread.
//   Location is global '??' at 0x7ffeda851000 ([stack]+0x00000001fb60)
//   Mutex M1 (0x7ffeda870b68) created at:
//     #0 pthread_mutex_init <null> (philo+0x44b47d)
//     #1 init_data /home/asrichar/Code/Cycle_03/pipex_failed/utils.c:51:2 (philo+0x4ba63d)
//     #2 main /home/asrichar/Code/Cycle_03/pipex_failed/main.c:107:6 (philo+0x4ba0fb)
//   Thread T6 (tid=127632, running) created by main thread at:
//     #0 pthread_create <null> (philo+0x449c4b)
//     #1 main /home/asrichar/Code/Cycle_03/pipex_failed/main.c:115:2 (philo+0x4ba166)
//   Thread T4 (tid=127630, finished) created by main thread at:
//     #0 pthread_create <null> (philo+0x449c4b)
//     #1 write_data_philos /home/asrichar/Code/Cycle_03/pipex_failed/utils.c:75:3 (philo+0x4ba9f2)
//     #2 main /home/asrichar/Code/Cycle_03/pipex_failed/main.c:109:2 (philo+0x4ba11c)
// SUMMARY: ThreadSanitizer: data race /home/asrichar/Code/Cycle_03/pipex_failed/main.c:32:16 in check_death
// ==================
// ThreadSanitizer: reported 1 warnings
// 1r4s12% ./philo 3 700 200 100
// 0 1 started
// 0 1 is eating
// 0 3 started
// 0 2 started
// 200 1 is sleeping
// 200 3 is eating
// 300 1 is thinking
// 400 3 is sleeping
// 400 2 is eating
// 500 3 is thinking
// 600 2 is sleeping
// 600 3 is eating
// 700 2 is thinking
// 800 3 is sleeping
// 800 1 is eating
// 900 3 is thinking
// 1000 1 died
// 1000 1 is sleeping
// 1000 1 is thinking
// ^C
// https://rom98759.github.io/Philosophers-visualizer/