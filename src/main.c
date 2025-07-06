/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:15:30 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/02 13:08:53 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Error\nUsage: ./philo count t_die t_eat t_sleep [eat_count]\n");
		return (1);
	}
	if (!check_args(argv))
		return (printf("Error\nMust be valid numbers!\n"), 1);
	init_data(&data);
	parse_args(&data, argv);
	// start_philo(&data);
	printf("args: %d, %d, %d, %d, %d\n", data.philo_count, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.eat_count);
	return (0);
}
