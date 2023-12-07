#include"philo.h"
int	check_param (int ac, char **av,s_param *data)
{
	if ((ac != 5 && ac != 6) || !av[1])
		return 0;
	data->n = ft_atoi (av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 5)
		data->t_teat = -1;
	else
		data->t_teat = ft_atoi(av[5]);
	if ((data->n <= 0 && data->n <= 200)|| data->t_die <= 0 || data->t_eat <= 0||
		data->t_sleep <= 0)
		return (0);
	return (1);
}

void    philo_infos(p_data *data,s_param *param)
{
    int i;

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

int init_data(p_data *data,s_param *param)
{
    int i;

    i = -1;
    data->ph = malloc(sizeof(p_philo ) * param->n);
    if (!data->ph)
        return 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * param->n);
    if (!data->forks)
        return 0;
    data->state = malloc(sizeof(pthread_mutex_t) * param->n);
    if (!data->state)
        return 0;
    data->th = malloc(sizeof(pthread_t) * param->n);
    if (!data->th)
        return 0;
    while (++i < param->n)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        pthread_mutex_init(&data->state[i], NULL);
    }
    philo_infos(data,param);
}

int start_simulation(s_param *param,p_data *data)
{
    int i;

    i = -1;
    get_time();
    while(++i < param->n)
        if (pthread_create(&data->th[i],NULL,routine,&data->ph[i]))
            return (1);
    return 0;
}

int   get_death(p_philo *philo)
{
    // printf("==== %lld==== \n",get_time() - philo->lm );
    if (get_time() - philo->lm >= philo->param->t_die)
        return (print_message(DEAD,philo),1);
    return (0);
}

void kill_philos(p_philo *philo,int body)
{
    int i;

    i = 0;
    while (i < philo->param->n)
    {
        if (body == i)
        {
            philo[i++].state = DEAD;
            continue ;
        }
        pthread_mutex_lock(philo[i].meals_control);
        philo[i].state = DEAD;
        pthread_mutex_unlock(philo[i].meals_control);
        i++;
    }
}

void    monitor_threads(p_data *data)
{
    int i;
    int flag;
    int b;

    i = 0;
    b = 1;
    while (1)
    {
        flag = 0;
        i = 0;
        while (i < data->ph->param->n)
        {
            pthread_mutex_lock(data->ph[i].meals_control);
            if(get_death(&data->ph[i]))
            {
                kill_philos(data->ph,i);
                b = 0;
                pthread_mutex_unlock(data->ph[i].meals_control);
                break;
            }
            if (data->ph[i].meals == data->ph->param->t_teat)
                flag++;
            pthread_mutex_unlock(data->ph[i].meals_control);
           i++;
        }
        if (flag == data->ph->param->n || !b)
            break ;
    }
//     if (flag)
//         pthread_mutex_unlock(data->ph[i].meals_control);
}

int main (int ac , char **av)
{
    s_param param;
    p_data  data;
    int i;

    i = -1;
    if (!check_param(ac ,av,&param))
        return (printf("INVALID PARAMETERS\n"),0);
    if (!init_data(&data,&param))
        return (printf("DATA INIT ERROR\n"),0);
    if (start_simulation(&param,&data))
        return (printf("CREATING THREADS EROOR\n"),0);
    monitor_threads(&data);
    if (param.n == 1)
        pthread_detach(data.th[0]);
    else
    {
        while (++i < param.n)
            if (pthread_join(data.th[i],NULL))
                 return (puts("here"),0);
        free(data.forks);
    }
    return (free (data.ph),free(data.state),1);
}