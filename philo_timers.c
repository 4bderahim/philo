
#include "philo.h"

long	time_(void)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = ((size_t)time.tv_sec * 1000) + ((size_t)time.tv_usec / 1000);
	return (result);
}

void	ft_usleep(long sleep_time)
{
	long start;

	start = time_();
	while (start + (sleep_time) > time_())
	{
		// check here for death to avoid delay in exiting!
		//(time_()
		//while ( time_() - philo->data->philosophers[i].last_time_ate) > philo->data->time_to_die
		usleep(500);
	}
}