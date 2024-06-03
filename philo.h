

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
struct s_tinfo
{
    pthread_mutex_t mutex;
    int p_id;  
};

typedef struct s_philo
{
    pthread_t thread;
    int philo_id;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    pthread_mutex_t *fork;
} t_philo;

