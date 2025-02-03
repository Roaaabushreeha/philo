/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:31:06 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/02/03 19:14:39 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
   
    t_philo *philo = (t_philo *)arg;
    
    while (philo->num_times_eat)
    {
        if (is_dead(philo))
            return NULL;

        print_action(philo, "is thinking\n");
        if (is_dead(philo)) return NULL;

        eating(philo);
        if (is_dead(philo)) return NULL;

        sleeping(philo);
        if (is_dead(philo)) return NULL;
         philo->num_times_eat--;
    }
    return NULL;
}

int dead(t_philo *philo)
{
    size_t current_time = get_time();

    if (is_dead(philo))
        return 1;

    if ((current_time - philo->last_meal) > philo->time_to_die)
    {
        print_action(philo, "has died\n");

        pthread_mutex_lock(&philo->data->death_mutex);
        philo->data->is_dead = 1;
        pthread_mutex_unlock(&philo->data->death_mutex);

        return 1; 
    }
    return 0; 
}
int is_dead(t_philo *philo)
//The is_dead function safely checks if a philosopher is dead by locking the associated mutex (death_mutex), 
//reading the is_dead status, and then unlocking the mutex. This ensures that the check 
//is done in a thread-safe manner, preventing race conditions that could arise if multiple threads tried to read or modify the death status simultaneously.
{
    pthread_mutex_lock(&philo->data->death_mutex);
    int status = philo->data->is_dead;
    pthread_mutex_unlock(&philo->data->death_mutex);
    return status;
}
void *monitor_routine(void *arg)
//This function is responsible for periodically checking if any philosopher has died 
//(i.e., if they haven't eaten in time and have exceeded the time they can survive without food).
//If any philosopher is found to be dead, the function prints the death message, updates the "death" status, and ends the monitoring routine.
{
   t_philo *philos = (t_philo *)arg;
    int i;

    while (1)
    {
        
        i = 0;
        while (i < philos->num_philos)
        {
            pthread_mutex_lock(&philos[i].data->death_mutex);
            if (get_time() - philos[i].last_meal > philos[i].time_to_die)
            {
                printf("%ld %d is dead\n", get_time() - philos[i].start_time, philos[i].id);
                philos[i].data->is_dead = 1;
                pthread_mutex_unlock(&philos[i].data->death_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&philos[i].data->death_mutex);
            i++;
        }
        
        usleep(1000);
    }
    return NULL;
}