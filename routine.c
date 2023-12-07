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

void    do_eating(p_philo *philo)
{
    if (!get_status(philo))
        return ;
    pthread_mutex_lock(philo->meals_control);
    if (philo->param->t_teat > -1)
        philo->meals++;
    // philo->state = EATING
    philo->lm = get_time();
    pthread_mutex_unlock(philo->meals_control);
    print_message(EATING,philo);
    my_usleep(philo->param->t_eat,philo);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    get_forks(p_philo *philo)
{
    if (!get_status(philo))
        return ;
    pthread_mutex_lock(philo->right_fork);
    if (!get_status(philo))
        return ;
    print_message(FORK,philo);
    pthread_mutex_lock(philo->left_fork);
    if (!get_status(philo))
        return ;
    print_message(FORK,philo);
}

void    do_sleeping(p_philo *philo)
{
    if (!get_status(philo))
        return ;
    print_message(SLEEPING,philo);
    my_usleep(philo->param->t_sleep,philo);
}

void    do_thinking(p_philo *philo)
{
    if (!get_status(philo))
        return ;
    print_message(THINKING,philo);
    my_usleep(1,philo);
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
    // puts("hello");
    }
    return (NULL);
}