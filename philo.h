

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


typedef struct s_data  t_data;
typedef struct s_fork
{
    pthread_mutex_t fork;
    int fork_id;
} t_fork;
typedef struct s_philosopher
{
    pthread_t thread;
    
    int philo_id;
    int full;
    int meals_count;
    t_fork *left_fork;
    t_fork *right_fork;
    t_fork  *forks;
    t_data *data;
    int *index;
} t_philosopher;
typedef struct s_data
{
    pthread_t thread;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int start_party;
    int end_party;
    int number_of_times_each_philosopher_must_eat;
    t_philosopher *philosophers;
    t_fork  *forks;
} t_data;
