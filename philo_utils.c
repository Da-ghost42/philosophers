#include"philo.h"

void	print_message(enum ph_state state ,p_philo *philo)
{
	char *p[] = {"is thinking","has taken fork","is eating","is sleeping","is DEAD"};
	printf("%llu %d %s\n",get_time(), philo->id,p[state]);
}

long long get_time(void)
{
	struct timeval	tv;
    static long long p;
	
	if (gettimeofday(&tv, NULL))
		error();
    if (p == 0)
        p = (tv.tv_sec * 1000) + tv.tv_usec / 1000;
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - p);
        
}

int ft_atoi(char *str)
{
	int i = 0;
	int r = 0;
	int s = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		r = r * 10 + str[i++] - 48;
	// if (r >= 200)
	// 	return -1;
	return (r * s);
}

void	ft_putstr_fd(char *str, int	fd)
{
	if (!*str)
		return ;
	while (*str)
		write (fd,&*str++,1);
}

void error()
{
	ft_putstr_fd("-----BAD ARGUMENTS-----\n", 1);
	ft_putstr_fd("The program arguments (all the arguments > 0) :\n", 1);
	ft_putstr_fd("./philo n t_die t_eat t_teat\n", 1);
	ft_putstr_fd("n : numbers of philos\n", 1);
	ft_putstr_fd("t_die : time to die\n", 1);
	ft_putstr_fd("t_eat : time to eat\n", 1);
	ft_putstr_fd("t_teat (optional) : number of meals\n", 1);
	exit (0);
}
