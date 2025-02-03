/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:34:26 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/02/03 19:16:08 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

int main(int ar,char **av)
{
    (void) ar;
    t_philo philo[PHILO_MAX];
    t_data  data;
    init_values(&data,av,philo);
    init_forks(philo);
    init_philo(philo,&data);
    init_thread(philo);
return 0;
}