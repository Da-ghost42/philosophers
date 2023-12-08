/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:06:48 by mboutuil          #+#    #+#             */
/*   Updated: 2023/12/08 13:19:27 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eating(t_philo *philo)
{
	if (!get_status (philo))
		return ;
	pthread_mutex_lock (philo->meals_control);
	if (philo->param->t_teat > -1)
		philo->meals++;
	philo->lm = get_time ();
	pthread_mutex_unlock (philo->meals_control);
	print_message (EATING, philo);
	my_usleep(philo->param->t_eat, philo);
}

void	get_forks(t_philo *philo)
{
	if (!get_status (philo))
		return ;
	pthread_mutex_lock (philo->right_fork);
	if (!get_status (philo))
		return ;
	print_message (FORK, philo);
	pthread_mutex_lock (philo->left_fork);
	if (!get_status (philo))
		return ;
	print_message (FORK, philo);
}

void	do_sleeping(t_philo *philo)
{
	if (!get_status (philo))
		return ;
	print_message (SLEEPING, philo);
	my_usleep (philo->param->t_sleep, philo);
}

void	do_thinking(t_philo *philo)
{
	if (!get_status (philo))
		return ;
	print_message (THINKING, philo);
	usleep(200);
}

void	kill_philos(t_philo *philo, int body)
{
	int	i;

	i = -1;
	while (++i < philo->param->n)
	{
		if (body == i)
		{
			philo[i].state = DEAD;
			continue ;
		}
		pthread_mutex_lock(philo[i].meals_control);
		philo[i].state = DEAD;
		pthread_mutex_unlock(philo[i].meals_control);
	}
}
