/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:08:46 by mboutuil          #+#    #+#             */
/*   Updated: 2023/12/08 01:57:46 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_infos(p_data *data, s_param *param)
{
	int	i;

	i = 0;
	while (i < param->n)
	{
		data->ph[i].id = i + 1;
		data->ph[i].lm = 0;
		data->ph[i].state = 0;
		data->ph[i].meals = 0;
		data->ph[i].param = param;
		data->ph[i].left_fork = &data->forks[i];
		data->ph[i].right_fork = &data->forks[(i + 1) % param->n];
		data->ph[i].meals_control = &data->state[i];
		if (data->ph[i].id % 2)
		{
			data->ph[i].left_fork = &data->forks[(i + 1) % param->n];
			data->ph[i].right_fork = &data->forks[i];
		}
		i++;
	}
}

int	start_simulation(s_param *param, p_data *data)
{
	int	i;

	i = -1;
	get_time();
	while (++i < param->n)
		if (pthread_create(&data->th[i], NULL, routine, &data->ph[i]))
			return (1);
	return (0);
}

int	get_death(p_philo *philo)
{
	if (get_time() - philo->lm >= philo->param->t_die)
		return (1);
	return (0);
}

void	monitor_threads(p_data *data)
{
	int	i;
	int	flag;
	int	b;

	while (1)
	{
		flag = 0;
		i = 0;
		while (i < data->ph->param->n)
		{
			pthread_mutex_lock(data->ph[i].meals_control);
			if (get_death(&data->ph[i]))
			{
				(kill_philos(data->ph, i), print_message(DEAD, &data->ph[i]));
				b = 0;
				pthread_mutex_unlock(data->ph[i].meals_control);
				break ;
			}
			if (data->ph[i].meals == data->ph->param->t_teat)
				flag++;
			pthread_mutex_unlock(data->ph[i].meals_control);
			i++;
		}
		if (flag == data->ph->param->n || !b)
			break ;
	}
}

int	main(int ac, char **av)
{
	s_param	param;
	p_data	data;
	int		i;

	i = -1;
	if (!check_param(ac, av, &param))
		return (printf("INVALID PARAMETERS\n"), 1);
	if (!init_data(&data, &param))
		return (printf("DATA INIT ERROR\n"), 1);
	if (start_simulation(&param, &data))
		return (printf("CREATING THREADS EROOR\n"), 1);
	monitor_threads(&data);
	if (param.n == 1)
		pthread_detach(data.th[0]);
	else
	{
		while (++i < param.n)
			if (pthread_join(data.th[i], NULL))
				return (1);
	}
	return (free (data.ph), free(data.forks), free(data.state), 0);
}
