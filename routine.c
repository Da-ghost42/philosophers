/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:06:52 by mboutuil          #+#    #+#             */
/*   Updated: 2023/12/08 01:10:39 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int get_status(p_philo *philo)
{
	int flag = 1;
	pthread_mutex_lock(philo->meals_control);
	if (philo->param->t_teat != -1 && philo->param->t_teat < philo->meals)
		flag = 0;
	if (philo->state == DEAD)
		flag = 0;
	pthread_mutex_unlock(philo->meals_control);
	return (flag);
}

void    my_usleep(long long time,p_philo *philo)
{
	long long start;

	start = get_time();
	while (get_time () - start < time)
	{
		if (get_status(philo) == 0)
			break ;
		usleep(200);
	}
}

void *routine(void *p)
{
	p_philo *philo = (p_philo *)p;

	while (get_status(philo))
	{
		get_forks(philo);
		do_eating(philo);
		do_sleeping(philo);
		do_thinking(philo);
	}
	return (NULL);
}