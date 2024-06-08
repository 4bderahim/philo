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
    data->number_of_philosophers = 5;
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
    
    data->philosophers->data = data;
    i = 0;
    while (i < data->number_of_philosophers)
    {
        mutex_calls(&data->forks[i].fork, 'i');
        data->forks[i].fork_id = i;
        i++;
        printf("#|\n");
    }
  
    set_philos(data, data->forks);
    i = 0;
    while (i < 5)
    {
        pthread_mutex_init(&data->forks[i].fork, NULL);
        data->philosophers[i].index = &i;
        
        

        pthread_create(&data->philosophers[i].thread, NULL, thread, &data->philosophers[i]);
        
        i++;
        printf("[#\n");
    }
    i = 0;
    data->i = 0;
    while (i < 5)
    {
        
        pthread_mutex_init(&(data->philosophers[i].left_fork->fork), NULL);
        pthread_mutex_init(&(data->philosophers[i].right_fork->fork), NULL);
        pthread_join(data->philosophers[i].thread, NULL);
        usleep(1);
       // pthread_mutex_unlock(&data->forks[0].fork);
//        pthread_mutex_destroy(&data->forks[0].fork);
        printf("\t||%d\n", i);
        i++;
    }
}
 pthread_mutex_t mut;
void *thread(void* arg)
{

    t_philosopher *ph;
    long int i;


    ph = (t_philosopher *)arg;
   pthread_mutex_lock(&(ph->left_fork->fork));
    printf("philo %d has taken left fork nbr : %d..\n", ph->philo_id, ph->left_fork->fork_id);
   pthread_mutex_lock(&(ph->right_fork->fork));
    printf("philo %d has taken right fork nbr : %d..\n", ph->philo_id, ph->right_fork->fork_id);
    i  = 0;
    printf("philo %d is eating..\n", ph->philo_id);
    while (i < 100000)
    {
   //      pthread_mutex_lock(&ph->left_fork->fork);
  //  pthread_mutex_lock(&ph->right_fork->fork);
        x++;
        i++;
  // pthread_mutex_unlock(&ph->left_fork->fork);
   // pthread_mutex_unlock(&ph->right_fork->fork);
    //pthread_mutex_unlock(&mut);
    }
    pthread_mutex_unlock(&(ph->left_fork->fork));
   pthread_mutex_unlock(&(ph->right_fork->fork));

    //  pthread_mutex_destroy(&ph->left_fork->fork);
    //  pthread_mutex_destroy(&ph->right_fork->fork);
   
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
