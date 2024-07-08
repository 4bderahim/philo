/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:51:06 by ael-krid          #+#    #+#             */
/*   Updated: 2024/07/06 18:51:07 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	set_forks_to_philos(t_data *data, int position)
{
	data->philosophers[position].right_fork = position;
	data->philosophers[position].left_fork = (position + 1)
		% data->number_of_philosophers;
}

void	set_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i].philo_id = i + 1;
		data->philosophers[i].meals_count = 0;
		data->philosophers[i].full = 0;
		data->philosophers[i].right_fork = i;
		data->dinner_end = 0;
		data->philosophers[i].last_time_ate = 0;
		data->time_start = time_();
		data->philosophers[i].philo_dead = 0;
		data->philosophers[i].left_fork = (i + 1)
			% data->number_of_philosophers;
		if (data->number_of_philosophers == 1)
			data->philosophers[i].left_fork = 1;
		data->philosophers[i].forks = data->forks;
		data->philosophers[i].data = data;
		data->all_meals = 0;
		i++;
	}
}

void	set_data_args(t_data *data, char **args, int argc)
{
	data->time_to_die = ph_atoi(args[2]);
	data->time_to_eat = ph_atoi(args[3]);
	data->time_to_sleep = ph_atoi(args[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = atoi(args[5]);
	else
		data->number_of_times_each_philosopher_must_eat = 0;
}