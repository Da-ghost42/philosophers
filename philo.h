/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:19:43 by mboutuil          #+#    #+#             */
/*   Updated: 2023/12/08 01:54:29 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
#include<stdbool.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

#define TRUE 1
#define MAX_THREAD 200
enum ph_state
{
	THINKING,
	FORK,
	EATING,
	SLEEPING,
	DEAD,
};

typedef struct p_param
{
    int				n;
/*------------------------*/
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_teat;
}s_param;

typedef struct s_philo
{
	int				id;
	int				meals; // PAY ATTENTION
	long long		lm; 	// PAY ATTENTION
	enum ph_state 	state; // PAY ATTENTION
    s_param          *param;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
    pthread_mutex_t  *meals_control;
}					p_philo;


typedef struct s_data
{//general infos
	struct s_philo *ph;
/*------------------------*/

	pthread_mutex_t *forks;
    pthread_mutex_t *state;
	pthread_t		*th;
	pthread_t		collect;
/*-----DEAD BODY--------*/
	int					b;
}					p_data;
/*---libft-tools---*/
void				error(void);
int					ft_atoi(char *str);
void				ft_putstr_fd(char *str, int fd);
/*-----------------*/
long long			get_time(void);
void	kill_philos(p_philo *philo, int body);
void	philo_infos(p_data *data, s_param *param);
void 	*routine(void *p);
void	sycronize_philos(p_philo *philo);
void	do_thinking(p_philo *philo);
void	do_sleeping(p_philo *philo);
void	get_forks(p_philo *philo);
void    my_usleep(long long time,p_philo *philo);
int		init_data(p_data *data, s_param *param);
/*--philosophers actions--*/ 
void				do_eating(p_philo *philo);
void				sleep_action(p_philo *philo);
void				print_message(enum ph_state state ,p_philo *philo);
int	check_param (int ac, char **av,s_param *data);
void				think_action(p_philo *philo);
/*----death checker----*/
int get_status(p_philo *philo);
void				*boddies_collecter(void *bodd);
#endif