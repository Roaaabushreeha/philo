/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:31:06 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/02/05 16:06:30 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		print_action(philo, "is thinking\n");
		if (eating(philo))
			return (NULL);
		if (is_dead(philo))
			return (NULL);
		sleeping(philo);
		if (is_dead(philo))
			return (NULL);
		if (philo->num_times_eat > 0)
		{
			philo->num_times_eat--;
			if (philo->num_times_eat == 0)
			{
				pthread_mutex_lock(&philo->data->death_mutex);
				pthread_mutex_unlock(&philo->data->death_mutex);
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	dead(t_philo *philo)
{
	size_t	current_time;

	current_time = get_time();
	if (is_dead(philo))
		return (1);
	if (philo->num_times_eat == 0)
	{
		philo->data->is_dead = 0;
		return (0);
	}
	if ((current_time - philo->last_meal) > philo->time_to_die)
	{
		print_action(philo, "has died\n");
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	return (0);
}

int	is_dead(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->data->death_mutex);
	status = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (status);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		i;
	int		finished;

	philos = (t_philo *)arg;
	while (1)
	{
		i = -1;
		finished = 0;
		while (++i < philos->num_philos)
		{
			pthread_mutex_lock(&philos[i].data->death_mutex);
			if (philos[i].num_times_eat == 0)
				finished++;
			if (monitor_routine2(philos, i))
				return (NULL);
			pthread_mutex_unlock(&philos[i].data->death_mutex);
		}
		if (finished == philos->num_philos)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	monitor_routine2(t_philo *philos, int i)
{
	if (philos->num_times_eat < 0)
	{
		if (get_time() - philos[i].last_meal > philos[i].time_to_die)
		{
			printf("%ld %d is dead\n", get_time() - philos[i].start_time,
				philos[i].id);
			philos[i].data->is_dead = 1;
			pthread_mutex_unlock(&philos[i].data->death_mutex);
			return (1);
		}
	}
	return (0);
}
