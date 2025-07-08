/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:55:59 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/08 19:37:12 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	while (i < data->philo_count)
		pthread_mutex_init(&data->forks[i++], NULL);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		data->philos[i].last_time_ate = data->start;
		i++;
	}
}

void	create_philos(t_data *data)
{
	int	i;

	i = 0;
	init_philos(data);
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			printf("Failed to create thread for philosopher %d\n",
				data->philos[i].id);
		data->philos[i].id = i + 1;
		i++;
	}
}

int	join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	if (pthread_join(data->monitor, NULL))
	{
		printf("Thread joining failed\n");
		// destroy(data);
		return (0);
	}
	return (1);
}

int	check_life(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_check_mutex);
		if ((timestamp() - data->philos[i].last_time_ate) > data->time_to_die)
		{
			printf_time(data->philos, "died", RED);
			data->died = 1;
			return (0);
		}
		pthread_mutex_unlock(&data->meal_check_mutex);
		i++;
	}
	return (1);
}

int	start_philo(t_data *data)
{
	create_forks(data);
	create_philos(data);
	if (pthread_create(&data->monitor, NULL, monitoring_loop, data) != 0)
	{
		printf("Thread creation failed\n");
		// destroy(data);
		return (0);
	}
	join(data);
	return (1);
}
void	*monitoring_loop(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	while (1)
	{
		if (!check_life(data))
			return (NULL);
		usleep(data->philo_count * 1000);
	}
	return (NULL);
}