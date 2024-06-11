#include "philo.h"
#include <sys/time.h>
long int x = 0;
void *thread(void* arg);

void set_forks_to_philos(t_data *data, int position)
{
    data->philosophers[position].right_fork = position;
    data->philosophers[position].left_fork = (position+1) % data->number_of_philosophers;
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
void d()
{
    system("leaks -q a.out");
}


void philo_creat(char **args)
{
    t_data *data;
    int i;
    i = 0;
    data = (t_data *) malloc(sizeof(t_data));
    if (!data)
       return ;
   printf("\t\t\t||%d||\n\n\n\n\n", atoi(args[1]));
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
    i = 0;
    while (i < data->number_of_philosophers)
    {
        printf("left > %d   <>  right %d\n", data->philosophers[i].left_fork,data->philosophers[i].right_fork );
        i++;
    }
    data->time_to_die = atoi(args[2]);
    data->time_to_eat = atoi(args[3]);
    data->time_to_sleep = atoi(args[4]);
    data->number_of_times_each_philosopher_must_eat = atoi(args[5]);
    
    i = 0;
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_init(&(data->forks[i].fork), NULL);
        pthread_mutex_init(&(data->philosophers[i].th_mutex), NULL);
        i++;
    }
    i = 0;
    while (i < data->number_of_philosophers)
    {
     //   pthread_mutex_init(&data->forks[i].fork, NULL);
        pthread_create(&data->philosophers[i].thread, NULL, thread, &data->philosophers[i]);
        i++;
    }
     
    i = 0;
    data->i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_join(data->philosophers[i].thread, NULL);
        usleep(1);
       // pthread_mutex_unlock(&data->forks[0].fork);
//        pthread_mutex_destroy(&data->forks[0].fork);
        printf("\t||%d\n", i);
        i++;
    }
}
void eating(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->th_mutex);
    printf("philo %d is eating..\n", philo->philo_id);
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->th_mutex);
}
void thinking(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->th_mutex);
    printf("philo %d is thinking..\n", philo->philo_id);
    pthread_mutex_unlock(&philo->th_mutex);
}
void left_fork(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->th_mutex);
    printf("philo %d has taken left fork..\n", philo->philo_id);
    pthread_mutex_unlock(&philo->th_mutex);
}
void right_fork(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->th_mutex);
    printf("philo %d has taken right fork..\n", philo->philo_id);
    pthread_mutex_unlock(&philo->th_mutex);
}
void sleeping(t_philosopher *philo)
{
    struct timeval start, end;
    
    
    printf("\t\t|%d||",end.tv_usec /  1000);
    pthread_mutex_lock(&philo->th_mutex);
    gettimeofday(&start, NULL);
    printf("philo %d is sleeping..\n", philo->philo_id);
    usleep(philo->data->time_to_sleep * 1000);
    gettimeofday(&end, NULL);
    if (((end.tv_usec) - (start.tv_usec)) >= (philo->data->time_to_sleep * 1000))
    {
        printf("philo %d \t\t\t\t\t------->  IS DEAD!", philo->philo_id);
    }
    pthread_mutex_unlock(&philo->th_mutex);
}
// make a func to set all millisecond related value elements //..
// int set_time(t_data *)
// {
//     //
// }
void *thread(void* arg)
{
    t_philosopher *ph;
    long int i;
    ph = (t_philosopher *) arg;
    if (ph->philo_id % 2 == 0)
    {
        thinking(ph);
      //  printf("philo %d is thinking..\n", ph->philo_id);
        usleep(10000);
    }
    // x; current time
    while (1)
    {
        // death -> check last time eat compared to current time eat: exit 
        usleep(40);
        thinking(ph);
        pthread_mutex_lock(&(ph->forks[ph->left_fork].fork));
        left_fork(ph);
        pthread_mutex_lock(&(ph->forks[ph->right_fork].fork));
        left_fork(ph);
        ph->meals_count++;
        eating(ph);
        
        printf("philo %d is sleeping..\n", ph->philo_id);
        sleeping(ph);
        pthread_mutex_unlock(&(ph->forks[ph->right_fork].fork));
        pthread_mutex_unlock(&(ph->forks[ph->left_fork].fork));    
        // philo is dead ?
        // if x >= arg--> time_to_die
        //      death;
        if (ph->meals_count == ph->data->number_of_times_each_philosopher_must_eat )
            {
                break;
                }
    } 
   return (0);
}


int main(int argc, char **argv)
{
    struct timeval start, end;
    int t, f;
    
    gettimeofday(&start, NULL);
    
    printf("\t start sec: %d\n", start.tv_usec);
    sleep(2);
    // philo_creat(argv);
    printf("threads are Done : %ld\n",x);
    gettimeofday(&end, NULL);
    printf("%d", ((end.tv_usec) - (start.tv_usec)));
    if (argc != 6)
        {
            printf("args!");
            return (0);
        }
    return (0);
}
