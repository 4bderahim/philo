#include "philo.h"
// kaaablaajjj

long int x = 0;
void *thread(void* arg)
{
    long int i;
    //t_philo * mutexx;
    // mutexx = (struct s_tinfo *)arg;
    i = 0;
    // pthread_mutex_lock(&mutexx->mutex);
    while (i < 100000000)
    {
        i++;
        x++;
    }
   // pthread_mutex_unlock(&mutexx->mutex);    
   
    return (0);
}
void set_forks_to_philos(t_data *data, int position)
{

    data->philosophers->left_fork = &data->philosophers[position].forks[position];
    data->philosophers->right_fork = &data->philosophers[position].forks[(position+1) % data->number_of_philosophers];
    if (data->philosophers->philo_id % 2)
    {
        data->philosophers->right_fork = &data->philosophers[position].forks[position];
        data->philosophers->left_fork = &data->philosophers[position].forks[(position+1) % data->number_of_philosophers];
    }
    int i = 0;
    while (i < data->number_of_philosophers)
    {
        printf("|philo id :%d\t\this left fork  :%p\n",data->philosophers[i].philo_id, &data->philosophers[i].left_fork);
        printf("|philo id :%d\t\this right fork :%p\n",data->philosophers[i].philo_id, &data->philosophers[i].right_fork);
        i++;
    }
}
//           1   (2)   2
//      (1)              (3)
//    0      {##}              
//  (5)             3
//   4     (4) 

void set_philos(t_data *struct_data, t_fork *fork)
{
    t_data *data;
    int i;
    i = 0;
    data = struct_data;

    while (i < data->number_of_philosophers)
    {
        data->philosophers->philo_id = i+1;
        data->philosophers->meals_count = 0;
        data->philosophers->full = 0;
        set_forks_to_philos(data,i);
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

void philo_creat()
{
    t_data *philo;
    int i;

    i = 0;
    philo = (t_data *) malloc(sizeof(t_data));
    if (!philo)
       return ;
    philo->number_of_philosophers = 5;
    philo->philosophers = (t_philosopher *) malloc(sizeof(t_philosopher)*philo->number_of_philosophers);
    
    if (!philo)
        {
            printf("[-] error in malloc\n");
            exit(1);
        }
    philo->forks = (t_fork *) malloc(sizeof(t_fork ) * philo->number_of_philosophers);
    if (!philo->forks)
        {
            printf("[-] error in malloc\n");
            exit(1);
        }
     i = 0;
    while (i < philo->number_of_philosophers)
    {
        mutex_calls(&philo->forks[i].fork, 'i');
        philo->forks[i].fork_id = i;
        i++;
    }
    i = 0;
    while (i < 5)
    {
        pthread_create(&philo->philosophers[i].thread, NULL, thread, philo);
        printf("\t[!] thread %d is alive\n", i+1);
        philo->philosophers[i].philo_id = i+1;    
        i++;
    }
    i = 0;
    set_philos(philo, philo->forks);
    while (i < philo->number_of_philosophers)
    {   
        printf("\tjoining philo:%p   id:%d \n",&philo->philosophers[i].thread, philo->philosophers[i].philo_id);
        pthread_join(philo->philosophers[i].thread, NULL);
        i++;
    } 
    i = 0;
    while (i < philo->number_of_philosophers)
    {   
        printf("\tphilo:%ld\tid:%d\tmeals count:%d \n",(long )(&philo->philosophers[i].thread), philo->philosophers[i].philo_id, philo->philosophers[i].meals_count);
        i++;
    }   
}
int dd()
{
    system("leaks -q a.out");
    return (0);
}

int main()
{
    // pthread_t threads[5];
    // pthread_mutex_t mutexx;
    // struct s_tinfo thread_struct;
    // thread_struct.mutex = mutexx;
    // pthread_mutex_init(&thread_struct.mutex, NULL);
    //atexit(dd());
    philo_creat();
    
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
