
#include "philo.h"

void end_dinner(t_data *data)
{

    int i;
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_destroy(&data->philosophers[i].forks->fork);
        
        pthread_detach(data->philosophers[i].thread);
        i++;
    }
    pthread_mutex_destroy(&data->th_mutex);
    pthread_mutex_destroy(&data->m_printf);
    free(data->forks);
    free(data->philosophers);
    free(data);
}
int set_mutex(t_data *data)
{
    int i;
    int error;

    i = 0;
    error = 0;
    while (i < data->number_of_philosophers)
    {
        if (pthread_mutex_init(&data->forks[i].fork, NULL))
            return (0);
        data->forks[i].fork_id = i;
        i++;
    }
    if (pthread_mutex_init(&(data->th_mutex), NULL))
        error =1;
    if (pthread_mutex_init(&(data->m_eat), NULL))
        error =1;
    if (pthread_mutex_init(&(data->m_printf), NULL))
        error =1;
    if (error)
    {
        free(data->forks);
        free(data->philosophers);
        free(data);
        return 0;
    }
    return (1);
}
int create_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        if (pthread_create(&data->philosophers[i].thread, NULL, thread, &data->philosophers[i]) != 0)
            {
                end_dinner(data);
                return (0);
            }

        i++;
    }
    return (1);
}
int join_threads(t_data *data)
{
    int i;
    int x;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        if (pthread_join(data->philosophers[i].thread, NULL))
            return (0);
        i++;
    }
    return (1);
}
int philo_creat(char **args,int argc )
{
    t_data *data;
    int i;
    i = 0;
    data = (t_data *) malloc(sizeof(t_data));
     if (!data)
        return (0);
    data->number_of_philosophers = ph_atoi(args[1]);
    data->philosophers = (t_philosopher *) malloc(sizeof(t_philosopher)*data->number_of_philosophers);
    if (!data->philosophers)
        return (0);
    data->forks = (t_fork *) malloc(sizeof(t_fork) *data->number_of_philosophers);
    if (!data->forks)
        return (0);
    i = 0;
    set_philos(data, data->forks);
    set_data_args(data,args, argc);
    if (!set_mutex(data))
        return (0);
    if (!create_threads(data))
        return (0);
    check_checks(data->philosophers);
    if (!join_threads(data))
        return (0);
    end_dinner(data);
    return (1);
}



void *thread(void* arg)
{
    t_philosopher *ph;
    long int i;
    ph = (t_philosopher *) arg;
    // printf("\t|%d\n", ph->philo_id);
    if (ph->philo_id % 2 == 0)
        usleep(1500);
    while (!check_(ph))
    {
        eating(ph);
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
    if (argc < 5 || check_args(argv, argc) == 0)
        {
            printf("Error : args!");
            return (0);
        }
    if (!philo_creat(argv, argc))
        printf("[-] Error!\n");

    //atexit(d);
    return (0);
}


