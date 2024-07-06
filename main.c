/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:51:06 by ael-krid          #+#    #+#             */
/*   Updated: 2024/07/06 18:51:07 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void end_dinner(t_data *data)
{

    int i;
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_destroy(&data->philosophers[i].forks->fork);
        pthread_detach(data->philosophers[i].thread);
        i++;
    }
    pthread_mutex_destroy(&data->th_mutex);
    pthread_mutex_destroy(&data->m_printf);
    free(data->forks);
    free(data->philosophers);
    free(data);
}

int philo_creat(char **args,int argc )
{
    t_data *data;
    int i;

    i = 0;
    data = (t_data *) malloc(sizeof(t_data));
     if (!data)
        return (0);
    data->number_of_philosophers = ph_atoi(args[1]);
    data->philosophers = (t_philosopher *) malloc(sizeof(t_philosopher)*data->number_of_philosophers);
    if (!data->philosophers)
        return (0);
    data->forks = (t_fork *) malloc(sizeof(t_fork) *data->number_of_philosophers);
    if (!data->forks)
        return (0);
    set_philos(data, data->forks);
    set_data_args(data,args, argc);
    if (!set_mutex(data))
        return (0);
    if (!create_threads(data))
        return (0);
    check_checks(data->philosophers);
    if (!join_threads(data))
        return (0);
    end_dinner(data);
    return (1);
}

void *thread(void* arg)
{
    t_philosopher *ph;
    long int i;
    ph = (t_philosopher *) arg;
    if (ph->philo_id % 2 == 0)
        usleep(1500);
    while (!check_(ph))
    {
        
        eating(ph);
        print_msg(ph, "is sleeping");
        ft_usleep((ph->data->time_to_sleep));
        print_msg(ph, "is thinking");
    } 
   return (0);
}
void d()
{
    system("leaks -q philo");
}

int main(int argc, char **argv)
{
    if (argc < 5 || check_args(argv, argc) == 0)
        {
            printf("[-] Error!\n");
            return (0);
        }
    if (!philo_creat(argv, argc))
        printf("[-] Error!\n");
    return (0);
}
