# include "philo.h"



// int gettimeofday(struct timeval *tv, struct timezone *tz);

long long get_time_in_ms (void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000LL) + (tv.tv_usec/1000));
}

void ft_usleep (size_t time_in_ms)
{
	long long start_time;
	start_time = get_time_in_ms();
	while((get_time_in_ms() - start_time) < (long long) time_in_ms)
	{
		usleep(100);
	}
}