#include "philo.h"

long int x = 0;
void *thread(void* arg);

void set_forks_to_philos(t_data *data, int position)
{
    data->philosophers[position].right_fork = &data->forks[position];
    data->philosophers[position].left_fork = &data->forks[(position+1) % data->number_of_philosophers];
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
        set_forks_to_philos(data, i);
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
void philo_creat()
{
    t_data *data;
    int i;
    i = 0;
    data = (t_data *) malloc(sizeof(t_data));
    if (!data)
       return ;
    data->number_of_philosophers = 4;
    data->philosophers = (t_philosopher *) malloc(sizeof(t_philosopher)*data->number_of_philosophers);
    if (!data->philosophers)
        {
            printf("[-] error in malloc\n");
            exit(1);
        }
    data->forks = (t_fork *) malloc(sizeof(t_fork) *data->number_of_philosophers);
    if (!data->forks)
        {
            printf("[-]a error in malloc\n");
            exit(1);
        }
    
    data->philosophers->data = data;
    i = 0;
    while (i < data->number_of_philosophers)
    {
        mutex_calls(&data->forks[i].fork, 'i');
        data->forks[i].fork_id = i;
        i++;
        printf("#\n");
    }
  
    set_philos(data, data->forks);
    i = 0;
    while (i < 4)
    {
        pthread_mutex_init(&data->forks[i].fork, NULL);
        data->philosophers[i].index = &i;
        //mutex_calls(&data->forks[i].fork, 'i');
        pthread_create(&data->philosophers[i].thread, NULL, thread, &data->forks[i]);
        i++;
        printf("#\n");
    }
    i = 0;
    while (i < 4)
    {
        pthread_join(data->philosophers[i].thread, NULL);
        //pthread_mutex_destroy(&data->forks[i].fork);
        i++;
        
    }
}

void *thread(void* arg)
{

    t_fork *ph;
    long int i;
    ph = (t_fork *)arg;
    
    i  = 0;
    pthread_mutex_lock(&ph->fork);
   while (i < 100000000)
   {
    
    x++;
    
    i++;
    
   }
   printf("fork %d <--\n", ph->fork_id);
   
   
   return (0);
}




//  i = 0;
    
//     while (i < data->number_of_philosophers)
//     {
//         printf("|philo id :%d\t\this left fork  :%d\n", data->philosophers[i].philo_id, data->philosophers[i].left_fork->fork_id);
//         printf("|philo id :%d\t\this right fork :%d\n\n", data->philosophers[i].philo_id,  data->philosophers[i].right_fork->fork_id);
//         i++;
//     }

int main()
{
    // pthread_t threads[5];
    // pthread_mutex_t mutexx;
    // struct s_tinfo thread_struct;
    // thread_struct.mutex = mutexx;
    // pthread_mutex_init(&thread_struct.mutex, NULL);
    //atexit(dd());
    
    philo_creat();
    printf("threads are Done : %ld\n",x);
    // i = 0;
    // while (i < 5)
    // {
    //     pthread_create(&threads[i], NULL, thread, &thread_struct);
    //     printf("[!] thread %d is alive\n", i);
    //     thread_struct.p_id = i;
         
    //     i++;
    // }
    // i = 0;
    // while (i < 5)
    // {
    //     //thread_struct.p_id = i;
    //     pthread_join(threads[i], NULL);
    //      printf("[+] thread %d is done\n", i);
    //     i++;
    // }
    // thread_struct.mutex = mutexx;
    

    // pthread_create(&threads, NULL, thread, &thread_struct);
    // pthread_create(&threads1, NULL, thread, &thread_struct);
    // pthread_join(threads, NULL);
    // pthread_join(threads1, NULL);
    
     //printf(">>%ld\n", x);
    // pthread_mutex_destroy(&mutexx);
    return (0);
}
