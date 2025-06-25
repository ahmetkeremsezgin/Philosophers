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
	printf("Usage: ./philo number_of_philosophers time_to_die ");
	printf("time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
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
		printf("Error: Failed to initialize data\n");
		return (1);
	}
	if (create_threads(&data))
	{
		printf("Error: Failed to create threads\n");
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}
