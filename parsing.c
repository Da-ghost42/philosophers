/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:41:04 by mboutuil          #+#    #+#             */
/*   Updated: 2023/12/08 10:31:24 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_param(int ac, char **av, t_param *data)
{
	if ((ac != 5 && ac != 6))
		return (0);
	data->n = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 5)
		data->t_teat = -1;
	else
		data->t_teat = ft_atoi(av[5]);
	if (data->n <= 0 || data->t_die <= 0 || data->t_eat <= 0
		|| data->t_sleep <= 0)
		return (0);
	return (1);
}

int	init_data(t_data *data, t_param *param)
{
	int	i;

	i = -1;
	data->ph = malloc(sizeof(t_philo) * param->n);
	if (!data->ph)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * param->n);
	if (!data->forks)
		return (free (data->ph), 0);
	data->state = malloc(sizeof(pthread_mutex_t) * param->n);
	if (!data->state)
		return (free (data->ph), free (data->forks), 0);
	data->th = malloc(sizeof(pthread_t) * param->n);
	if (!data->th)
		return (free (data->ph), free (data->forks), free(data->state), 0);
	while (++i < param->n)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->state[i], NULL);
	}
	philo_infos(data, param);
	return (1);
}
