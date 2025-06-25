/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:15:30 by mabaghda          #+#    #+#             */
/*   Updated: 2025/06/25 18:30:44 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	// pthread_t	thread;

	if (!check_args(argc, argv))
	{
		printf("Error\nUsage: ./philo count t_die t_eat t_sleep [eat_count]\n");
		return (1);
	}
	return (0);
}
