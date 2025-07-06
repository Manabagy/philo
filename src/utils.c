/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:48:26 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/06 18:02:14 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_data(t_data *data)
{
	data->forks = NULL;
	data->philo_count = 0;
	data->start = 0;
	data->eat_count = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
}

int	ft_atoi(const char *str)
{
	int	a;
	int	integer;
	int	sign;

	a = 0;
	integer = 0;
	sign = 1;
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == 32)
		a++;
	if (str[a] == '+')
		a++;
	else if (str[a] == '-')
	{
		sign = -1;
		a++;
	}
	while (str[a] && (str[a] >= '0' && str[a] <= '9'))
	{
		integer = integer * 10 + (str[a] - '0');
		a++;
	}
	return (integer * sign);
}

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (1)
	{
		// if (philo->id % 2 != 0)
		printf("%lld %d is thinking\n", timestamp(), philo->id);
		// if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d is eating\n", timestamp(), philo->id);
	}
}