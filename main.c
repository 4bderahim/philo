


#include "philo.h"
#include <sys/time.h>
long	get_time(void)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = ((size_t)time.tv_sec * 1000) + ((size_t)time.tv_usec / 1000);
	return (result);
}
void	ft_usleep(long sleep_time)
{
	long	start;

	start = get_time();
	while (start + (sleep_time * 1) > get_time())
		usleep(100);
}
long	time_(void)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = ((size_t)time.tv_sec * 1000) + ((size_t)time.tv_usec / 1000);
	return (result);
}
long int x = 0;
void *thread(void* arg);

void set_forks_to_philos(t_data *data, int position)
{
    data->philosophers[position].right_fork = position;
    data->philosophers[position].left_fork = (position+1) % data->number_of_philosophers;
}
void print_msg(t_philosopher *philo, char *msg)
{
    pthread_mutex_lock(&philo->data->m_printf);
    if (!philo->data->dinner_end)
    {
        printf("%ld %d %s\n",get_time() - philo->data->time_start , philo->philo_id, msg);
    }
    pthread_mutex_unlock(&philo->data->m_printf);
}
void set_death(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->th_mutex);
    philo->data->dinner_end =1;
    pthread_mutex_unlock(&philo->th_mutex);
}
void check_checks(t_philosopher *philo)
{
    int i;
    i = 0;

    while (!philo->data->dinner_end)
    {
        
        i = 0;
        
        while (i < philo->data->number_of_philosophers)
        {
        // if ((philo->data->number_of_times_each_philosopher_must_eat != 0) && (philo->data->number_of_philosophers == philo->data->philosophers[i].meals_count))
		// {
		// 	set_death(philo);
		// 	break ;
		// }
            if (philo->data->philosophers[i].last_time_ate != 0 &&( (get_time() - philo->data->philosophers[i].last_time_ate) > philo->data->time_to_die))
            {
                 print_msg(&philo->data->philosophers[i], "died");
                 set_death(philo);
                 break;
            }
            i++;
            //usleep(1000);
        }
    }
}
void set_philos(t_data *data, t_fork *fork)
{
    int i;
    i = 0;
    while (i < data->number_of_philosophers)
    {
        data->philosophers[i].philo_id = i+1;
        data->philosophers[i].meals_count = 0;
        data->philosophers[i].full = 0;
        data->philosophers[i].right_fork = i;
        data->dinner_end = 0;
        data->philosophers[i].last_time_ate = 0;
        data->time_start = 0;
        data->philosophers[i].philo_dead = 0;
        data->philosophers[i].left_fork = (i+1) % data->number_of_philosophers;
        if (data->number_of_philosophers == 1)
            data->philosophers[i].left_fork = 1;
        data->philosophers[i].forks = data->forks;
        data->philosophers[i].data = data;
        //set_forks_to_philos(data, i);
        i++;
    }
}
void mutex_calls(pthread_mutex_t *mutex, char order)
{
    if (order == 'i')
        pthread_mutex_init(mutex ,NULL);
    else if (order == 'l')
        pthread_mutex_lock(mutex);
    else if (order == 'u')
        pthread_mutex_unlock(mutex);
    else if (order == 'd')
        pthread_mutex_destroy(mutex);
}

void end_dinner(t_data *data)
{

    int i;
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_destroy(&data->philosophers[i].forks->fork);
        pthread_mutex_destroy(&data->philosophers[i].th_mutex);
        pthread_detach(data->philosophers[i].thread);
        i++;
    }
    pthread_mutex_destroy(&data->m_printf);
    free(data->forks);
    free(data->philosophers);
    free(data);
}
void set_data_args(t_data *data, char **args)
{
    data->time_to_die = atoi(args[2]);
    data->time_to_eat = atoi(args[3]);
    data->time_to_sleep = atoi(args[4]);
    data->number_of_times_each_philosopher_must_eat = atoi(args[5]);
}
void philo_creat(char **args)
{
    t_data *data;
    int i;
    i = 0;
    data = (t_data *) malloc(sizeof(t_data));
    if (!data)
       return ;
   //printf("\t\t\t||%d||\n\n\n\n\n", atoi(args[1]));
    data->number_of_philosophers = atoi(args[1]);
    data->philosophers = (t_philosopher *) malloc(sizeof(t_philosopher)*data->number_of_philosophers);
    if (!data->philosophers)
        {
            printf("[-] error in malloc\n");
            exit(1);
        }
    data->forks = (t_fork *) malloc(sizeof(t_fork) *data->number_of_philosophers);
    if (!data->forks)
        {
            printf("[-] error in malloc\n");
            exit(1);
        }
    i = 0;
    while (i < data->number_of_philosophers)
    {
        mutex_calls(&data->forks[i].fork, 'i');
        data->forks[i].fork_id = i;
        i++;
    }
    set_philos(data, data->forks);
    set_data_args(data,args);
    
    i = 0;
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_init(&(data->forks[i].fork), NULL);
        pthread_mutex_init(&(data->philosophers[i].th_mutex), NULL);
        i++;
    }
    pthread_mutex_init(&(data->m_eat), NULL);
    pthread_mutex_init(&(data->m_printf), NULL);
    i = 0;
    data->time_start = time_();
    while (i < data->number_of_philosophers)
    {
        //pthread_mutex_init(&data->forks[i].fork, NULL);
        pthread_create(&data->philosophers[i].thread, NULL, thread, &data->philosophers[i]);
        i++;
    }
    check_checks(data->philosophers);
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_join(data->philosophers[i].thread, NULL);
        i++;
    }
    end_dinner(data);
}
void set_eattime(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->th_mutex);
    philo->last_time_ate = time_();
    pthread_mutex_unlock(&philo->th_mutex);
}
void set_done_eating(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->th_mutex);
    philo->data->dinner_end = time_();
    pthread_mutex_unlock(&philo->th_mutex);
}

void eating(t_philosopher *philo)
{
    struct timeval end, start;
   
    pthread_mutex_lock(&philo->forks[philo->left_fork].fork);
    print_msg(philo, "has taken a fork");
    pthread_mutex_lock(&philo->forks[philo->right_fork].fork);
    print_msg(philo, "has taken a fork");
    //pthread_mutex_lock(&philo->data->m_eat);
    
    print_msg(philo, "is eating");
    set_eattime(philo);
    philo->meals_count++;
    ft_usleep((philo->data->time_to_eat));
    
    if (philo->meals_count == philo->data->number_of_times_each_philosopher_must_eat)
        set_done_eating(philo);
   //pthread_mutex_unlock(&philo->data->m_eat);
    
    pthread_mutex_unlock(&philo->forks[philo->right_fork].fork);
    pthread_mutex_unlock(&philo->forks[philo->left_fork].fork);
}
void *thread(void* arg)
{
    t_philosopher *ph;
    long int i;
    ph = (t_philosopher *) arg;
    if (ph->philo_id % 2 == 0)
    {
        //print_msg(ph, "is thinking");
        usleep(1000);
    }
    while (!ph->data->dinner_end)
    {
        eating(ph);
        if (ph->data->philosophers[i].meals_count == ph->data->number_of_times_each_philosopher_must_eat)
            {
                set_death(ph);
                break;
            }
        print_msg(ph, "is sleeping");
        ft_usleep((ph->data->time_to_sleep));
        print_msg(ph, "is thinking");
    } 
   return (0);
}
void d()
{
    system("leaks -q a.out");
}
int main(int argc, char **argv)
{
    if (argc != 6)
        {
            printf("args!");
            return (0);
        }
     philo_creat(argv);
     
    atexit(d);
    return (0);
}


