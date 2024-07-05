#include "philo.h"

int check_(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->m_eat);

    if (philo->data->dinner_end)
    {
        pthread_mutex_unlock(&philo->data->m_eat);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->m_eat);
    return (0);
}

int check_full(t_data *data)
{
    int i;
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_lock(&data->m_eat);
        if (data->number_of_times_each_philosopher_must_eat == 0) 
            {
                pthread_mutex_unlock(&data->m_eat);        
                return 0;
            }
        if (data->philosophers[i].meals_count != data->number_of_times_each_philosopher_must_eat)
            {
                pthread_mutex_unlock(&data->m_eat);
                return (0);
            }
        i++;
        pthread_mutex_unlock(&data->m_eat);
    }
    return (1);
}
void check_checks(t_philosopher *philo)
{
    int i;
    i = 0;

    while (!check_(philo))
    {
        
        i = 0;
        long g;
        while (i < philo->data->number_of_philosophers)
        {
        if (check_full(philo->data))
                {
                    set_death(philo);
                    break;
                }
            pthread_mutex_lock(&philo->data->m_eat);
            if (philo->data->philosophers[i].last_time_ate &&  (time_() - philo->data->philosophers[i].last_time_ate) >= philo->data->time_to_die)
            {
                pthread_mutex_unlock(&philo->data->m_eat);
                print_msg(&philo->data->philosophers[i], "died");
                set_death(philo);
                 
                 break;
            }
            pthread_mutex_unlock(&philo->data->m_eat);
            i++;
        }
    }
}



