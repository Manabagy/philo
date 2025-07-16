/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:55:59 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/16 17:01:00 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
	{
		printf("Failed to allocate forks");
		return (0);
	}
	while (i < data->philo_count)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
	{
		printf("Failed to allocate philos");
		return (0);
	}
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eaten = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		data->philos[i].last_time_ate = data->start;
		i++;
	}
	return (1);
}

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	if (!init_philos(data))
		return (0);
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
		{
			printf("Failed to create thread for philosopher %d\n",
				data->philos[i].id);
			destroy(data);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->monitor, NULL) != 0)
	{
		printf("Thread joining failed\n");
		destroy(data);
		return (0);
	}
	while (i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			printf("Thread joining failed\n");
			destroy(data);
			return (0);
		}
		i++;
	}
	return (1);
}

int	start_philo(t_data *data)
{
	pthread_mutex_lock(&data->meal_check_mutex);
	data->start = time_now();
	pthread_mutex_unlock(&data->meal_check_mutex);
	if (!create_forks(data))
	{
		destroy(data);
		return (0);
	}
	if (!create_philos(data))
	{
		destroy(data);
		return (0);
	}
	if (pthread_create(&data->monitor, NULL, monitoring_loop, data) != 0)
	{
		printf("Thread creation failed\n");
		destroy(data);
		return (0);
	}
	join(data);
	destroy(data);
	return (1);
}
