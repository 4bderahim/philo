/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:51:06 by ael-krid          #+#    #+#             */
/*   Updated: 2024/07/06 18:51:07 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

void					*thread(void *arg);

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;
typedef struct s_philosopher
{
	pthread_t			thread;

	int					philo_id;
	int					meals_count;
	int					left_fork;
	int					right_fork;
	t_fork				*forks;
	t_data				*data;
	long int			last_time_ate;
}						t_philosopher;
typedef struct s_data
{
	pthread_t			thread;
	long int			time_start;
	pthread_mutex_t		m_eat;
	pthread_mutex_t		m_printf;
	pthread_mutex_t		th_mutex;
	int					all_meals;
	int					n_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					dinner_end;
	int					n_must_eat;
	t_philosopher		*philosophers;
	t_fork				*forks;
}						t_data;
int						check_args(char **argv, int argc);
int						ph_atoi(char *s);
void					ft_usleep(long sleep_time, t_philosopher *philo);
long					time_(void);
int						check_(t_philosopher *philo);
void					check_checks(t_philosopher *philo);
void					eating(t_philosopher *philo);
void					print_msg(t_philosopher *philo, char *msg);
void					set_death(t_philosopher *philo);
void					set_data_args(t_data *data, char **args, int argc);
void					set_philos(t_data *data);
void					set_forks_to_philos(t_data *data, int position);
void					end_dinner(t_data *data);
int						set_mutex(t_data *data);
int						create_threads(t_data *data);
int						join_threads(t_data *data);
#endif