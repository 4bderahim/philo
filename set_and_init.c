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

	i = 0;
	while (i < data->n_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			return (0);
		data->forks[i].fork_id = i;
		i++;
	}
	i = 0;
	if (pthread_mutex_init(&(data->th_mutex), NULL))
		i = 1;
	if (pthread_mutex_init(&(data->m_eat), NULL))
		i = 1;
	if (pthread_mutex_init(&(data->m_printf), NULL))
		i = 1;
	if (i == 1)
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
	while (i < data->n_of_philos)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, thread,
				&data->philosophers[i]) != 0)
		{
			end_dinner(data);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philos)
	{
		if (pthread_join(data->philosophers[i].thread, NULL) != 0)
		{
			end_dinner(data);
			return (0);
		}
		i++;
	}
	return (1);
}
