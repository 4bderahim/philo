#include "philo.h"


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
    if (philo == NULL)
        printf("[_] #&&#\n\n\n");
    printf("[_] seg is %zu|%d Below \n\n\n\n", sizeof(t_philosopher ), philo->number_of_philosophers);
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
        philo->forks[i].fork_id = i+1;
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
    while (i < philo->number_of_philosophers)
    {   
        printf("\tjoining philo:%p   id:%d \n",&philo->philosophers[i].thread, philo->philosophers[i].philo_id);
       
        pthread_join(philo->philosophers[i].thread, NULL);
        
        i++;
    } 
    i = 0;
    while (i < philo->number_of_philosophers)
    {   
        printf("\tphilo:%ld   id:%d\n",(long )(&philo->philosophers[i].thread), philo->philosophers[i].philo_id);
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
