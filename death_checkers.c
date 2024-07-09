/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:51:06 by ael-krid          #+#    #+#             */
/*   Updated: 2024/07/06 18:51:07 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_(t_philosopher *philo)
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

int	check_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philos)
	{
		pthread_mutex_lock(&data->m_eat);
		if (data->n_must_eat == 0)
		{
			pthread_mutex_unlock(&data->m_eat);
			return (0);
		}
		if (data->philosophers[i].meals_count < data->n_must_eat)
		{
			pthread_mutex_unlock(&data->m_eat);
			return (0);
		}
		pthread_mutex_unlock(&data->m_eat);
		i++;
	}
	return (1);
}

void	check_checks(t_philosopher *philo)
{
	int		i;
	long	l_eat;

	while (!check_(philo))
	{
		i = 0;
		while (i < philo->data->n_of_philos)
		{
			if (check_full(philo->data))
			{
				set_death(philo);
				break ;
			}
			pthread_mutex_lock(&philo->data->m_eat);
			l_eat = philo->data->philosophers[i].last_time_ate;
			if (l_eat && (time_() - l_eat) >= philo->data->time_to_die)
			{
				pthread_mutex_unlock(&philo->data->m_eat);
				print_msg(&philo->data->philosophers[i], "died");
				break ;
			}
			pthread_mutex_unlock(&philo->data->m_eat);
			i++;
		}
	}
}
