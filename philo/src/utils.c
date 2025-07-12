/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:48:26 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/12 19:27:52 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_data(t_data *data)
{
	data->start = time_now();
	data->died = 0;
	data->done = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_check_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->died_mutex, NULL);
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

	time = time_now() - philo->data->start;
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->eat_mutex);
	pthread_mutex_lock(&philo->data->died_mutex);
	if (!philo->data->died && !philo->data->done)
		printf("%s[%lld] %d %s%s\n", color, time, philo->id, str, RESET);
	pthread_mutex_unlock(&philo->data->died_mutex);
	pthread_mutex_unlock(&philo->data->eat_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
