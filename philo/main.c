/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:10:12 by asezgin           #+#    #+#             */
/*   Updated: 2025/06/25 13:10:12 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phlio.h"
#include <unistd.h>

static int	validate_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

static void	print_usage(void)
{
	write(1, "Usage: ./philo number_of_philosophers time_to_die ", 50);
	write(1, "time_to_eat time_to_sleep ", 26);
	write(1, "[number_of_times_each_philosopher_must_eat]\n", 45);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!validate_args(argc, argv))
	{
		print_usage();
		return (1);
	}
	if (init_data(&data, argc, argv))
	{
		write(1, "Error: Failed to initialize data\n", 34);
		return (1);
	}
	if (create_threads(&data))
	{
		write(1, "Error: Failed to create threads\n", 33);
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}
