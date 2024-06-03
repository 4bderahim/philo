#include "philo.h"


long int x = 0;
void *thread(void* arg)
{
    
    long int i;
    struct s_tinfo *mutexx;
    mutexx = (struct s_tinfo *)arg;

    i = 0;
    pthread_mutex_lock(&mutexx->mutex);
    while (i < 100000000)
    {
        i++;
        x++;
    }
    pthread_mutex_unlock(&mutexx->mutex);    
   
    return (0);
}

void philo_creat()
{
    t_philo *philo;
    int i;
    
    i = 0;
    philo = (t_philo *) malloc(sizeof(philo->number_of_philosophers));
    if (!philo)
        {
            printf("[-] error in malloc\n");
            exit(1);
        }
    philo->fork = (pthread_mutex_t *) malloc(sizeof(philo->number_of_philosophers));
    if (!philo->fork)
        {
            printf("[-] error in malloc\n");
            exit(1);
        }
    while (i < philo->number_of_philosophers)
    {
        pthread_mutex_init(philo[i].fork, NULL);
        philo[i].philo_id = i;
        i++;
    }
    
}

int main()
{
    pthread_t threads[5];
    pthread_mutex_t mutexx;
    struct s_tinfo thread_struct;
    thread_struct.mutex = mutexx;
    pthread_mutex_init(&thread_struct.mutex, NULL);
    
    int i;
    i = 0;
    while (i < 5)
    {
        pthread_create(&threads[i], NULL, thread, &thread_struct);
        printf("[!] thread %d is alive\n", i);
        thread_struct.p_id = i;
         
        i++;
    }
    i = 0;
    while (i < 5)
    {
        //thread_struct.p_id = i;
        pthread_join(threads[i], NULL);
         printf("[+] thread %d is done\n", i);
        i++;
    }
    
    // thread_struct.mutex = mutexx;
    

    // pthread_create(&threads, NULL, thread, &thread_struct);
    // pthread_create(&threads1, NULL, thread, &thread_struct);
    // pthread_join(threads, NULL);
    // pthread_join(threads1, NULL);
    
     printf(">>%ld\n", x);
    // pthread_mutex_destroy(&mutexx);
    return (0);
}
