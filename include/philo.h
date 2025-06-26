/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:15:57 by mabaghda          #+#    #+#             */
/*   Updated: 2025/06/26 19:22:30 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
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
	int					time_to_die;
	int					time_to_sleep;
	long				start;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_data;

int						check_args(char **argv);
int						ft_atoi(const char *str);
void					init_data(t_data *data);
void					parse_args(t_data *data, char **argv);
void					start_philo(t_data *data);

#endif