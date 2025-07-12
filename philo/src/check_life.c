/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:28:29 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/12 19:31:38 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_life(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_check_mutex);
		if ((time_now() - data->philos[i].last_time_ate) > data->time_to_die)
		{
			printf_time(&data->philos[i], "died", RED);
			data->died = 1;
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

	i = 0;
	pthread_mutex_lock(&data->eat_mutex);
	if (data->eat_count == -1)
	{
		pthread_mutex_unlock(&data->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->eat_mutex);
	while (i < data->philo_count && !data->died)
	{
		pthread_mutex_lock(&data->eat_mutex);
		if (data->philos[i].eaten >= data->eat_count)
			i++;
		pthread_mutex_unlock(&data->eat_mutex);
	}
	if (i == data->philo_count)
	{
		data->done = 1;
		return (printf("Dinner end\n"), 0);
	}
	return (1);
}

void	*monitoring_loop(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (!check_life(data) || !done_eating(data))
			break ;
		usleep(500);
	}
	return (NULL);
}
