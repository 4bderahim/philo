


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
        data->dinner_end = 0;
        data->philosophers[i].last_time_ate.tv_sec = 0;
        data->philosophers[i].last_time_ate.tv_usec = 0;
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
   //printf("\t\t\t||%d||\n\n\n\n\n", atoi(args[1]));
    data->number_of_philosophers = atoi(args[1]);
    data->end_party = 0;
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
        //pthread_mutex_init(&(data->philosophers[i].th_mutex), NULL);
        i++;
    }
    pthread_mutex_init(&(data->m_eat), NULL);
    pthread_mutex_init(&(data->m_printf), NULL);
    pthread_mutex_init(&(data->m_sleep), NULL);
    pthread_mutex_init(&(data->m_think), NULL);
    pthread_mutex_init(&(data->m_left_fork), NULL);
    pthread_mutex_init(&(data->m_right_fork), NULL);

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
        // printf("\t||%d\n", i);
        i++;
    }
}
void ph_eating(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->m_printf);
    printf("philo %d is eating..\n", philo->philo_id);
    pthread_mutex_unlock(&philo->data->m_printf);
}
int eating(t_philosopher *philo)
{
    struct timeval end, start;
    start = philo->last_time_ate;
    pthread_mutex_lock(&philo->data->m_eat);
    gettimeofday(&end, NULL);
    // printf("\t[\t#%ld]\n", start.tv_sec);
    // printf("\t\t[time spent: %ld ~ time to spend:%d]\n", (((((end.tv_sec - start.tv_sec) * 1000000)) + (end.tv_usec - start.tv_usec)) / 1000),philo->data->time_to_die);
    
    if (start.tv_sec != 0 && ((( ((end.tv_sec - start.tv_sec) * 1000000)) + (end.tv_usec - start.tv_usec)) / 1000) >= (philo->data->time_to_die ))
    {
        philo->data->dinner_end = 1;
        pthread_mutex_unlock(&philo->data->m_eat);
        pthread_mutex_lock(&philo->data->m_printf);
        printf("philo %d -------> IS DEAD!####|\n", philo->philo_id);
        pthread_mutex_unlock(&philo->data->m_printf);
        
        return (1);
    }
    ph_eating(philo);
    usleep(philo->data->time_to_eat * 1000);
    gettimeofday(&philo->last_time_ate, NULL);
    pthread_mutex_unlock(&philo->data->m_eat);
    return (0);
}
void ph_thinking(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->m_printf);
    printf("philo %d is thinking..\n", philo->philo_id);
    pthread_mutex_unlock(&philo->data->m_printf);
}
int thinking(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->m_think);
    if (philo->data->dinner_end == 1)
            {
                pthread_mutex_unlock(&philo->data->m_think);
                return (1);
            }
    ph_thinking(philo);
    pthread_mutex_unlock(&philo->data->m_think);
    return (0);
}


int check_dinner_end(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->th_mutex);
    if (philo->data->dinner_end == 1)
            {
                pthread_mutex_unlock(&philo->th_mutex);
                return (1);
            }
    pthread_mutex_unlock(&philo->th_mutex);
    return (0);
}
void ph_left_fork(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->m_printf);            
    printf("philo %d has taken left fork..\n", philo->philo_id);
    pthread_mutex_unlock(&philo->data->m_printf);
    
}
int left_fork(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->m_left_fork);
    if (philo->data->dinner_end == 1)
            {
                pthread_mutex_unlock(&philo->data->m_left_fork);
                return (1);
            }
    ph_left_fork(philo);
    pthread_mutex_unlock(&philo->data->m_left_fork);
    return (0);
}
void ph_right_fork(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->m_printf);
    printf("philo %d has taken right fork..\n", philo->philo_id);
    pthread_mutex_unlock(&philo->data->m_printf);
}
int right_fork(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->m_right_fork);
    if (philo->data->dinner_end == 1)
            {
               pthread_mutex_unlock(&philo->data->m_right_fork);
               return (1);
            }
    ph_right_fork(philo);
    pthread_mutex_unlock(&philo->data->m_right_fork);
    return (0);
}

void spread_the_word(t_data *data)
{
    int i;
    i = 0;
    data->dinner_end = 1;
}

void ph_sleeping(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->m_printf);
    printf("philo %d is sleeping..\n", philo->philo_id);
    pthread_mutex_unlock(&philo->data->m_printf);
}
int sleeping(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->m_sleep);
    if (philo->data->dinner_end == 1)
            {
                
                pthread_mutex_unlock(&philo->data->m_sleep);
                return (1);
            }
    ph_sleeping(philo);
    usleep(philo->data->time_to_sleep * 1000);
    pthread_mutex_unlock(&philo->data->m_sleep);
    return (0);
}

void *thread(void* arg)
{
    t_philosopher *ph;
    long int i;
    ph = (t_philosopher *) arg;
    if (ph->philo_id % 2 == 0)
    {
        if (thinking(ph))
            return NULL;
      //  printf("philo %d is thinking..\n", ph->philo_id);
        usleep(1000);
    }
    while (1)
    {
        // pthread_mutex_lock(&ph->th_mutex);
        // if (ph->data->dinner_end == 1)
        //     {
        //         pthread_mutex_unlock(&ph->th_mutex);
        //         break;
        //     }
        // pthread_mutex_unlock(&ph->th_mutex);
        //usleep(40);

        if (thinking(ph))
            break;
        pthread_mutex_lock(&(ph->forks[ph->left_fork].fork));

        if (left_fork(ph))
            {
                pthread_mutex_unlock(&(ph->forks[ph->left_fork].fork)); 
                break;
            }
        pthread_mutex_lock(&(ph->forks[ph->right_fork].fork));
        if (right_fork(ph))
            {
                pthread_mutex_unlock(&(ph->forks[ph->right_fork].fork));
                pthread_mutex_unlock(&(ph->forks[ph->left_fork].fork));  
                break;
            }

        ph->meals_count++;
        if (eating(ph))
            {
                pthread_mutex_unlock(&(ph->forks[ph->right_fork].fork));
                pthread_mutex_unlock(&(ph->forks[ph->left_fork].fork));    
                break;
            }

        //printf("philo %d is sleeping..\n", ph->philo_id);
        if (sleeping(ph))
           {
                pthread_mutex_unlock(&(ph->forks[ph->right_fork].fork));
                pthread_mutex_unlock(&(ph->forks[ph->left_fork].fork));  
             break;
           }
        pthread_mutex_unlock(&(ph->forks[ph->right_fork].fork));
        pthread_mutex_unlock(&(ph->forks[ph->left_fork].fork));    
    } 
   return (0);
}


int main(int argc, char **argv)
{
    struct timeval start, end;
    int t, f;
    
    gettimeofday(&start, NULL);
    
    printf("\t start sec: %ld\n", start.tv_sec);
    sleep(2);
    gettimeofday(&end, NULL);
    //printf("|\t | : %ld\n", end.tv_sec);
     philo_creat(argv);
    // long seconds = end.tv_sec - start.tv_sec;
    // long microseconds = end.tv_usec - start.tv_usec;
    // long elapsed_microseconds = seconds * 1000000 + microseconds;

    
   // printf("%ld", ( ( ((end.tv_sec - start.tv_sec) * 1000000)  + (end.tv_usec - start.tv_usec))  / 1000));
    if (argc != 6)
        {
            printf("args!");
            return (0);
        }
    return (0);
}


// #include "philo.h"
// #include <sys/time.h>
// long int x = 0;
// void *thread(void* arg);

// void set_forks_to_philos(t_data *data, int position)
// {
//     data->philosophers[position].right_fork = position;
//     data->philosophers[position].left_fork = (position+1) % data->number_of_philosophers;
// }

// void set_philos(t_data *data, t_fork *fork)
// {
//     int i;
//     i = 0;
//     while (i < data->number_of_philosophers)
//     {
//         data->philosophers[i].philo_id = i+1;
//         data->philosophers[i].meals_count = 0;
//         data->philosophers[i].full = 0;
//         data->philosophers[i].right_fork = i;
//         data->dinner_end = 0;
//         data->philosophers[i].last_time_ate.tv_sec = 0;
//         data->philosophers[i].last_time_ate.tv_usec = 0;
//         data->philosophers[i].left_fork = (i+1) % data->number_of_philosophers;
//         if (data->number_of_philosophers == 1)
//             data->philosophers[i].left_fork = 1;
//         data->philosophers[i].forks = data->forks;
//         data->philosophers[i].data = data;
//         //set_forks_to_philos(data, i);
//         i++;
//     }
// }
// void mutex_calls(pthread_mutex_t *mutex, char order)
// {
//     if (order == 'i')
//         pthread_mutex_init(mutex ,NULL);
//     else if (order == 'l')
//         pthread_mutex_lock(mutex);
//     else if (order == 'u')
//         pthread_mutex_unlock(mutex);
//     else if (order == 'd')
//         pthread_mutex_destroy(mutex);
// }
// void d()
// {
//     system("leaks -q a.out");
// }


// void philo_creat(char **args)
// {
//     t_data *data;
//     int i;
//     i = 0;
//     data = (t_data *) malloc(sizeof(t_data));
//     if (!data)
//        return ;
//    //printf("\t\t\t||%d||\n\n\n\n\n", atoi(args[1]));
//     data->number_of_philosophers = atoi(args[1]);
//     data->end_party = 0;
//     data->philosophers = (t_philosopher *) malloc(sizeof(t_philosopher)*data->number_of_philosophers);
//     if (!data->philosophers)
//         {
//             printf("[-] error in malloc\n");
//             exit(1);
//         }
//     data->forks = (t_fork *) malloc(sizeof(t_fork) *data->number_of_philosophers);
//     if (!data->forks)
//         {
//             printf("[-] error in malloc\n");
//             exit(1);
//         }
//     i = 0;
//     while (i < data->number_of_philosophers)
//     {
//         mutex_calls(&data->forks[i].fork, 'i');
//         data->forks[i].fork_id = i;
//         i++;
//     }
//     set_philos(data, data->forks);
//     i = 0;
//     while (i < data->number_of_philosophers)
//     {
//         printf("left > %d   <>  right %d\n", data->philosophers[i].left_fork,data->philosophers[i].right_fork );
//         i++;
//     }
//     data->time_to_die = atoi(args[2]);
//     data->time_to_eat = atoi(args[3]);
//     data->time_to_sleep = atoi(args[4]);
//     data->number_of_times_each_philosopher_must_eat = atoi(args[5]);
    
//     i = 0;
//     while (i < data->number_of_philosophers)
//     {
//         pthread_mutex_init(&(data->forks[i].fork), NULL);
//         pthread_mutex_init(&(data->philosophers[i].th_mutex), NULL);
//         i++;
//     }
//     i = 0;
//     while (i < data->number_of_philosophers)
//     {
//      //   pthread_mutex_init(&data->forks[i].fork, NULL);
//         pthread_create(&data->philosophers[i].thread, NULL, thread, &data->philosophers[i]);
//         i++;
//     }
//     i = 0;
//     data->i = 0;
//     while (i < data->number_of_philosophers)
//     {
//         pthread_join(data->philosophers[i].thread, NULL);
//         usleep(1);
//         // pthread_mutex_unlock(&data->forks[0].fork);
//         //pthread_mutex_destroy(&data->forks[0].fork);
//         printf("\t||%d\n", i);
//         i++;
//     }
// }
// int eating(t_philosopher *philo)
// {
//     struct timeval end, start;

    
//     pthread_mutex_lock(&philo->th_mutex);

//     pthread_mutex_lock(&philo->th_mutex);
//     start = philo->last_time_ate;
//     pthread_mutex_unlock(&philo->th_mutex);
//     gettimeofday(&end, NULL);
//     printf("\t[\t#%ld]\n", start.tv_sec);
//     printf("\t\t[time spent: %ld ~ time to spend:%d]\n", (((((end.tv_sec - start.tv_sec) * 1000000)) + (end.tv_usec - start.tv_usec)) / 1000),philo->data->time_to_die);
    
//     if (start.tv_sec != 0 && ((( ((end.tv_sec - start.tv_sec) * 1000000)) + (end.tv_usec - start.tv_usec)) / 1000) >= (philo->data->time_to_die ))
//     {

//         pthread_mutex_unlock(&philo->th_mutex);
        
//         printf("philo %d -------> IS DEAD!####|\n", philo->philo_id);
//         philo->data->dinner_end =1;
//         return (1);
//     }
//     printf("philo %d is eating..\n", philo->philo_id);
//     usleep(philo->data->time_to_eat * 1000);
//     gettimeofday(&philo->last_time_ate, NULL);
//   //  printf("#######!@!@\n");
//     pthread_mutex_unlock(&philo->th_mutex);
//     return (0);
// }
// int thinking(t_philosopher *philo)
// {
//     pthread_mutex_lock(&philo->th_mutex);
//     if (philo->data->dinner_end == 1)
//             {
//                 pthread_mutex_unlock(&philo->th_mutex);
//                 return (1);
//             }
//     printf("philo %d is thinking..\n", philo->philo_id);
//     pthread_mutex_unlock(&philo->th_mutex);
//     return (0);
// }
// int check_dinner_end(t_philosopher *philo)
// {
//     pthread_mutex_lock(&philo->th_mutex);
//     if (philo->data->dinner_end == 1)
//             {
//                 pthread_mutex_unlock(&philo->th_mutex);
//                 return (1);
//             }
//     pthread_mutex_unlock(&philo->th_mutex);
//     return (0);
// }
// int left_fork(t_philosopher *philo)
// {
//     pthread_mutex_lock(&philo->th_mutex);
//     if (philo->data->dinner_end == 1)
//             {
//                 pthread_mutex_unlock(&philo->th_mutex);
//                 return (1);
//             }
//     printf("philo %d has taken left fork..\n", philo->philo_id);
//     pthread_mutex_unlock(&philo->th_mutex);
//     return (0);
// }
// int right_fork(t_philosopher *philo)
// {
//     pthread_mutex_lock(&philo->th_mutex);
//     if (philo->data->dinner_end == 1)
//             {
//                pthread_mutex_unlock(&philo->th_mutex);
//                 return (1);
//             }
//     printf("philo %d has taken right fork..\n", philo->philo_id);
//     pthread_mutex_unlock(&philo->th_mutex);
//     return (0);
// }

// void spread_the_word(t_data *data)
// {
//     int i;
//     i = 0;
//     data->dinner_end = 1;
// }
// int sleeping(t_philosopher *philo)
// {
//     pthread_mutex_lock(&philo->th_mutex);
//     if (philo->data->dinner_end == 1)
//             {
                
//                 pthread_mutex_unlock(&philo->th_mutex);
//                 return (1);
//             }
//     printf("philo %d is sleeping..\n", philo->philo_id);
//     usleep(philo->data->time_to_sleep * 1000);
//     pthread_mutex_unlock(&philo->th_mutex);
//     return (0);
// }

// void *thread(void* arg)
// {
//     t_philosopher *ph;
//     long int i;
//     ph = (t_philosopher *) arg;
//     if (ph->philo_id % 2 == 0)
//     {
//         if ( thinking(ph))
//             return NULL;
//         usleep(10000);
//     }
//     while (1)
//     {
//         pthread_mutex_lock(&ph->th_mutex);
//         if (ph->data->dinner_end == 1)
//             {
//                 pthread_mutex_unlock(&ph->th_mutex);
//                 printf("\t+++++> DEaD1\n");
//                 break;
//             }
//         pthread_mutex_unlock(&ph->th_mutex);
//         if (thinking(ph) == 1)
//             break;
//         pthread_mutex_lock(&(ph->forks[ph->left_fork].fork));
//         if (left_fork(ph))
//             {
                
//                 pthread_mutex_unlock(&(ph->forks[ph->left_fork].fork));  
//                 break;
//             }
//         pthread_mutex_lock(&(ph->forks[ph->right_fork].fork));
//         if (right_fork(ph))
//             {
//                 pthread_mutex_lock(&(ph->forks[ph->left_fork].fork));
//                 pthread_mutex_unlock(&(ph->forks[ph->right_fork].fork));
//                 break;
//             }
//         ph->meals_count++;
//         if (eating(ph))
//             {
//                 pthread_mutex_unlock(&(ph->forks[ph->right_fork].fork));
//                 pthread_mutex_unlock(&(ph->forks[ph->left_fork].fork));   
//                 break;
//             }
//         else{
//             pthread_mutex_unlock(&(ph->forks[ph->right_fork].fork));
//             pthread_mutex_unlock(&(ph->forks[ph->left_fork].fork));   

//         }
//         printf("philo %d is sleeping..\n", ph->philo_id);
//         if (sleeping(ph))
//            {
//             pthread_mutex_unlock(&(ph->forks[ph->right_fork].fork));
//             pthread_mutex_unlock(&(ph->forks[ph->left_fork].fork));   
//             break;
//            }
//     } 
//    return (0);
// }


// int main(int argc, char **argv)
// {
//     struct timeval start, end;
//     int t, f;
    
//     gettimeofday(&start, NULL);
    
//     printf("\t start sec: %ld\n", start.tv_sec);
//     sleep(2);
//     gettimeofday(&end, NULL);
//     //printf("|\t | : %ld\n", end.tv_sec);
//      philo_creat(argv);
//     // long seconds = end.tv_sec - start.tv_sec;
//     // long microseconds = end.tv_usec - start.tv_usec;
//     // long elapsed_microseconds = seconds * 1000000 + microseconds;

    
//    // printf("%ld", ( ( ((end.tv_sec - start.tv_sec) * 1000000)  + (end.tv_usec - start.tv_usec))  / 1000));
//     if (argc != 6)
//         {
//             printf("args!");
//             return (0);
//         }
//     return (0);
// }







