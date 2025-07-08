/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:48:26 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/08 19:40:03 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	init_data(t_data *data)
{
	data->forks = NULL;
	data->philo_count = 0;
	data->start = timestamp();
	data->eat_count = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->died = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_check_mutex, NULL);
	// pthread_mutex_init(&data->died, NULL);
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

void	printf_time(t_philo *philo, char *str, char *color)
{
	long long	time;

	time = timestamp() - philo->data->start;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->died)
		printf("%s[%lld] %d %s%s\n", color, time, philo->id, str, RESET);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		printf_time(philo, "has taken a fork", RED);
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (1)
	{
		// if (!check_life(philo))
		// 	return (NULL);
		main_loop(philo);
	}
	return (NULL);
}

void	main_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf_time(philo, "has taken a fork", WHITE);
	pthread_mutex_lock(philo->right_fork);
	printf_time(philo, "has taken a fork", WHITE);
	printf_time(philo, "is eating", GREEN);
	usleep(philo->data->time_to_eat * 1000);
	philo->last_time_ate = timestamp();
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	printf_time(philo, "is sleeping", CYAN);
	usleep(philo->data->time_to_sleep * 1000);
	printf_time(philo, "is thinking", YELLOW);
}
