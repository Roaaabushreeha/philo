/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:33:45 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/02/05 15:57:38 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork\n");
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_action(philo, "is sleeping\n");
	if (ft_usleep(philo->data->time_to_sleep, philo))
	{
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	if (philo->num_philos == 1)
	{
		one_philo(philo);
		return (1);
	}
	if (philo->num_times_eat < 0)
	{
		if (is_dead(philo))
			return (1);
	}
	lock_forks(philo);
	if (is_dead(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	print_action(philo, "is eating\n");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_usleep(philo->data->time_to_eat, philo);
	unlock_forks(philo);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (is_dead(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	print_action(philo, "is thinking\n");
	return (0);
}
