/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:15:57 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/08 18:26:03 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	long long			last_time_ate;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					philo_count;
	int					eat_count;
	int					time_to_eat;
	long long			time_to_die;
	int					time_to_sleep;
	long				start;
	int					died;
	pthread_mutex_t		died_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		meal_check_mutex;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_data;

int						check_args(char **argv);
int						ft_atoi(const char *str);
void					init_data(t_data *data);
void					parse_args(t_data *data, char **argv);
void					start_philo(t_data *data);
void					*philo_routine(void *arg);
long long				timestamp(void);
void					printf_time(t_philo *philo, char *str);
int						check_life(t_philo *philo);

#endif