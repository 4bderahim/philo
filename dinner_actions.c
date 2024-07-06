/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:51:06 by ael-krid          #+#    #+#             */
/*   Updated: 2024/07/06 18:51:07 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

void	set_death(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->m_eat);
	philo->data->dinner_end = 1;
	pthread_mutex_unlock(&philo->data->m_eat);
}

void	set_eattime(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->m_eat);
	philo->last_time_ate = time_();
	pthread_mutex_unlock(&philo->data->m_eat);
}

void	set_meals_count(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->m_eat);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->data->m_eat);
}

void	print_msg(t_philosopher *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->m_printf);
	pthread_mutex_lock(&philo->data->m_eat);
	if (!philo->data->dinner_end)
	{
		printf("%ld %d %s\n", time_() - philo->data->time_start,
			philo->philo_id, msg);
	}
	pthread_mutex_unlock(&philo->data->m_eat);
	pthread_mutex_unlock(&philo->data->m_printf);
}

void	eating(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->forks[philo->left_fork].fork);
	print_msg(philo, "has taken a fork");
	if (philo->data->number_of_philosophers == 1)
        {
			print_msg(philo, "died");
			set_death(philo);
        }
	pthread_mutex_lock(&philo->forks[philo->right_fork].fork);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	set_eattime(philo);
	ft_usleep((philo->data->time_to_eat), philo);
	set_meals_count(philo);
	pthread_mutex_unlock(&philo->forks[philo->right_fork].fork);
	pthread_mutex_unlock(&philo->forks[philo->left_fork].fork);
}