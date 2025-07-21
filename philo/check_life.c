/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:28:29 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/21 10:37:35 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_life(t_data *data)
{
	int	i;
	int	full_copy;

	i = 0;
	pthread_mutex_lock(&data->eat_mutex);
	full_copy = data->full;
	pthread_mutex_unlock(&data->eat_mutex);
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_check_mutex);
		if (((time_now() - data->philos[i].last_time_ate) > data->time_to_die)
			&& !full_copy)
		{
			printf_time(&data->philos[i], "died", RED);
			pthread_mutex_lock(&data->died_mutex);
			data->died = 1;
			pthread_mutex_unlock(&data->died_mutex);
			pthread_mutex_unlock(&data->meal_check_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->meal_check_mutex);
		i++;
	}
	return (1);
}

int	done_eating(t_data *data)
{
	int	i;
	int	full;

	if (data->eat_count == -1)
		return (1);
	full = 0;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->eat_mutex);
		if (data->philos[i].eaten >= data->eat_count)
			full++;
		pthread_mutex_unlock(&data->eat_mutex);
		i++;
	}
	if (full == data->philo_count)
	{
		pthread_mutex_lock(&data->died_mutex);
		data->done = 1;
		pthread_mutex_unlock(&data->died_mutex);
		return (printf("Dinner end\n"), 0);
	}
	return (1);
}

void	*monitoring_loop(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	usleep(1000);
	while (1)
	{
		if (!check_life(data))
			break ;
		if (!done_eating(data))
			break ;
		usleep(500);
	}
	return (NULL);
}

void	ft_usleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = time_now();
	while ((time_now() - start) < time)
	{
		pthread_mutex_lock(&philo->data->died_mutex);
		if (philo->data->died)
		{
			pthread_mutex_unlock(&philo->data->died_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->died_mutex);
		usleep(100);
	}
}
