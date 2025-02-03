/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:46:28 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/02/03 19:09:12 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_values(t_data *data,char **av,t_philo *philo)
//This initializes a mutex specifically used for managing
// access to resources related to the "death" condition of 
//threads (in the context of the philosopher problem, for instance). The death_mutex is likely used to prevent concurrent
// modification of shared variables that track whether a philosopher has died.
//In summary, these mutexes are used to prevent race conditions by locking critical sections where shared resources 
//(like death status, printed output, and other data) are being modified or accessed by multiple threads.
{
    philo->num_philos=ft_atoi(av[1]);
    data->time_to_eat=ft_atoilong(av[3]);
    data->time_to_die=ft_atoilong(av[2]);
    data->time_to_sleep=ft_atoilong(av[4]);
    data->is_dead = 0;
    data->stop_flag = 1;
    if (av[5])
        data->num_times_eat = ft_atoi(av[5]);
    else
        data->num_times_eat = -1;
    pthread_mutex_init(&data->death_mutex, NULL);
    pthread_mutex_init(&data->printf_mutex, NULL);
    pthread_mutex_init(&data->data_mutex, NULL);
}
int init_forks(t_philo *philo)
{
   int i;

    i = 0;
    while (i < philo->num_philos)
    {
        if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
        {
            write(2, "init mutex failed!\n", 19);
            return 1;
        }
        i++;
    }
    return(0);
}
int init_philo(t_philo *philo,t_data *data)
{
     int i = 0;
    while (i < philo->num_philos)
    {
      philo[i].num_times_eat = data->num_times_eat;
        philo[i].time_to_sleep = data->time_to_sleep;
        philo[i].time_to_eat = data->time_to_eat;
        philo[i].time_to_die = data->time_to_die;
        philo[i].meals_eaten = 0;
        philo[i].id = i + 1;
        philo[i].left_fork = &philo->forks[i];
        philo[i].right_fork = &philo->forks[(i + 1) % philo->num_philos];
        philo[i].start_time = get_time();
        philo[i].last_meal = get_time();
        philo[i].data = data;
        i++;
    }
    return 0;
}
int init_thread(t_philo *philo)
{
    int i = 0;
    pthread_t monitor_thread;

    while (i < philo->num_philos)
    {
        if (pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]))
        {
            perror("Error creating thread for philosopher");
            return (1);
        }
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, &monitor_routine, philo))
    {
        perror("Error creating monitor thread");
        return (1);
    }

    i = 0;
    while (i < philo->num_philos)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
      pthread_join(monitor_thread, NULL);
    return 0;
}