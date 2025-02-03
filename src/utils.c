/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:59:01 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/02/03 15:30:20 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

long	ft_atoilong(const char *nptr)
{
	int	i;
	long	res;
	int	sign;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

size_t get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);  
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000)); 
}
int ft_usleep(size_t ms)
{
	size_t start;

	start=get_time();
	while(get_time()-start <ms)
	{
		 usleep(500);
	}
	return 0;
}
void print_action(t_philo *philo, const char *action)
{
    long time_get;

    pthread_mutex_lock(&philo->data->printf_mutex);
    pthread_mutex_lock(&philo->data->death_mutex);
    
    // Stop printing actions if the simulation is marked as stopped
    if (philo->data->is_dead && ft_strcmp(action, "has died\n") != 0)
    {
        pthread_mutex_unlock(&philo->data->death_mutex);
        pthread_mutex_unlock(&philo->data->printf_mutex);
        return;
    }
    
   time_get= get_time() - philo->start_time;
    printf("%ld philo %d %s", time_get, philo->id, action);

    pthread_mutex_unlock(&philo->data->death_mutex);
    pthread_mutex_unlock(&philo->data->printf_mutex);
}
