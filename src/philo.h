/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:24:19 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/02/03 15:26:52 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
#define PHILO_MAX 200
typedef struct s_data
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				proper_meals;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	data_mutex;
	int meals_eaten;
	int 	num_times_eat;
	 int             is_dead;
	 int				stop_flag;
	pthread_mutex_t *forks;
}t_data;
typedef struct s_philo
{
	size_t start_time;
	size_t	 last_meal; 
	size_t			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_t thread;
	int id;
	int num_times_eat;
	int meals_eaten;
	int flag_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;	
	int num_philos;
	 pthread_mutex_t	forks[PHILO_MAX];
	t_data 			*data;
}	t_philo;
int ft_strcmp(const char *s1, const char *s2);
void init_values(t_data *data,char **av,t_philo *philo);
int init_forks(t_philo *philo);
void print_action(t_philo *philo, const char *action);
void *philo_routine(void *arg);
int ft_usleep(size_t ms);
int is_dead(t_philo *philo);
size_t  get_time(void);
int init_philo(t_philo *philo,t_data *data);
int	ft_atoi(const char *nptr);
long	ft_atoilong(const char *nptr);
void lock_forks(t_philo *philo);
void unlock_forks(t_philo *philo);
int sleeping (t_philo *philo);
int eating(t_philo *philo);
int init_thread(t_philo *philo);
void *monitor_routine(void *arg);
int thinking(t_philo *philo);
int dead(t_philo *philo);
#endif