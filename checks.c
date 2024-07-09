/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:51:06 by ael-krid          #+#    #+#             */
/*   Updated: 2024/07/06 18:51:07 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_atoi(char *s)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (s[i] != 0)
	{
		if (s[i] == '+')
		{
			if (!(s[i + 1] >= '0' && s[i + 1] <= '9'))
				return (-1);
			i++;
		}
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (-1);
		res = (res * 10) + (s[i] - 48);
		i++;
	}
	return (res);
}

int	check_args(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ph_atoi(argv[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}
