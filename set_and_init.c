/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_and_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:51:06 by ael-krid          #+#    #+#             */
/*   Updated: 2024/07/06 18:51:07 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	set_mutex(t_data *data)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			return (0);
		data->forks[i].fork_id = i;
		i++;
	}
	if (pthread_mutex_init(&(data->th_mutex), NULL))
		error = 1;
	if (pthread_mutex_init(&(data->m_eat), NULL))
		error = 1;
	if (pthread_mutex_init(&(data->m_printf), NULL))
		error = 1;
	if (error == 1)
	{
		free(data->forks);
		free(data->philosophers);
		free(data);
		return (0);
	}
	return (1);
}

int	create_threads(t_data *data)
{
	int	i;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, thread,
				&data->philosophers[i]) != 0)
		{
            
            //sleep(5);
			//end_dinner(data);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->philosophers[i].thread, NULL))
		{
			end_dinner(data);
			return (0);
		}
		i++;
	}
	return (1);
}