/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:15:30 by mabaghda          #+#    #+#             */
/*   Updated: 2025/06/25 19:31:45 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	// pthread_t	thread;
	if (argc < 5 || argc > 6)
	{
		printf("Error\nUsage: ./philo count t_die t_eat t_sleep [eat_count]\n");
		return (1);
	}
	if (!check_args(argv))
		return (printf("Error\nMust be only numbers!\n"), 1);
	init_data(&data);
	parse_args(&data, argv);
	// printf("%d\n", data.time_to_eat);
	return (0);
}
