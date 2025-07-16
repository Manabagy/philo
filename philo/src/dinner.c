/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:21:30 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/16 12:34:27 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_philo *philo)
{
	printf_time(philo, "is eating", GREEN);
	philo->last_time_ate = time_now();
	usleep(philo->data->time_to_eat * 1000);
	if (philo->data->eat_count != -1)
	{
		pthread_mutex_lock(&philo->data->eat_mutex);
		philo->eaten++;
		pthread_mutex_unlock(&philo->data->eat_mutex);
	}
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf_time(philo, "has taken a fork", WHITE);
		pthread_mutex_lock(philo->right_fork);
		printf_time(philo, "has taken a fork", WHITE);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf_time(philo, "has taken a fork", WHITE);
		pthread_mutex_lock(philo->left_fork);
		printf_time(philo, "has taken a fork", WHITE);
	}
}

static void	leave_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	main_loop(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->died_mutex);
		if (philo->data->died || philo->data->done)
		{
			pthread_mutex_unlock(&philo->data->died_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->died_mutex);
		take_forks(philo);
		eat(philo);
		leave_forks(philo);
		printf_time(philo, "is sleeping", CYAN);
		usleep(philo->data->time_to_sleep * 1000);
		printf_time(philo, "is thinking", YELLOW);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		printf_time(philo, "has taken a fork", WHITE);
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(500);
	main_loop(philo);
	return (NULL);
}
