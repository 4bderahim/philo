

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
    int     left_fork;
    int     right_fork;
    pthread_mutex_t th_mutex;
    t_fork  *forks;
    t_data *data;
    long int last_time_ate;
    int philo_dead;
    // int dinner_end;
    int *index;
} t_philosopher;
typedef struct s_data
{
    pthread_t thread;
    long int  time_start;
    pthread_mutex_t m_sleep;
    pthread_mutex_t m_think;
    pthread_mutex_t m_eat;
    pthread_mutex_t m_printf;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat; //
    int time_to_sleep;
    int start_party;
    int end_party;
    int dinner_end;
    int number_of_times_each_philosopher_must_eat;
    t_philosopher *philosophers;
    int i;
    t_fork  *forks;
} t_data;
