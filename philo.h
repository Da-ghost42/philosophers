/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:19:43 by mboutuil          #+#    #+#             */
/*   Updated: 2023/12/08 02:25:46 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

enum e_state
{
	THINKING,
	FORK,
	EATING,
	SLEEPING,
	DEAD,
};

typedef struct s_param
{
	int				n;
/*------------------------*/
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_teat;
}	t_param;

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		lm;
	enum e_state	state;
	t_param			*param;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*meals_control;
}				t_philo;

typedef struct s_data
{
	struct s_philo	*ph;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*state;
	pthread_t		*th;
	pthread_t		collect;
	int				b;
}					t_data;

void				error(void);
int					ft_atoi(char *str);
void				ft_putstr_fd(char *str, int fd);
long long			get_time(void);
void				kill_philos(t_philo *philo, int body);
void				philo_infos(t_data *data, t_param *param);
void				*routine(void *p);
void				do_thinking(t_philo *philo);
void				do_sleeping(t_philo *philo);
void				get_forks(t_philo *philo);
void				my_usleep(long long time, t_philo *philo);
int					init_data(t_data *data, t_param *param);
void				do_eating(t_philo *philo);
void				print_message(enum e_state state, t_philo *philo);
int					check_param(int ac, char **av, t_param *data);
int					get_status(t_philo *philo);
#endif