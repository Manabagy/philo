/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:55:59 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/08 18:27:41 by mabaghda         ###   ########.fr       */
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

void	join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	check_life(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_count)
	{
		pthread_mutex_lock(&philo->data->meal_check_mutex);
		if ((timestamp() - philo->last_time_ate) > philo->data->time_to_die)
		{
			printf_time(philo, "has died");
			philo->data->died = 1;
			return (0);
		}
		pthread_mutex_unlock(&philo->data->meal_check_mutex);
		i++;
	}
	return (1);
}

void	start_philo(t_data *data)
{
	create_forks(data);
	create_philos(data);
	join(data);
	// check_life(data->philos);
}
