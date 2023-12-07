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
