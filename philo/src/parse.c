/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:46:13 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/01 15:37:49 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	overflow(char *str)
{
	int		sign;
	long	result;
	int		i;

	sign = 1;
	result = 0;
	i = 0;
	while (!(str[i] >= '0' && str[i] <= '9'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (sign == 1 && result > 2147483647)
			return (0);
		if (sign == -1 && (-result) < -2147483648)
			return (0);
		i++;
	}
	return (1);
}

static int	letters_and_signs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || str[i] == '-' || !overflow(str))
			return (0);
		i++;
	}
	return (1);
}

void	parse_args(t_data *data, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->eat_count = ft_atoi(argv[5]);
	else
		data->eat_count = -1;
}

int	check_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!letters_and_signs(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
