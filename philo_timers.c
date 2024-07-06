
#include "philo.h"

long	time_(void)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = ((size_t)time.tv_sec * 1000) + ((size_t)time.tv_usec / 1000);
	return (result);
}

void	ft_usleep(long sleep_time, t_philosopher *philo)
{
	long start;

	start = time_();
	while (start + (sleep_time) > time_())
	{
		if (check_(philo))
			break;
		usleep(500);
	}
}