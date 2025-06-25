/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42 <42@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42                #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by 42               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phlio.h"

static void	cleanup_philos(t_data *data)
{
	int	i;

	if (!data->philos)
		return ;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].eat_mutex);
		i++;
	}
	free(data->philos);
	data->philos = NULL;
}

static void	cleanup_forks(t_data *data)
{
	int	i;

	if (!data->forks)
		return ;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

static void	cleanup_threads(t_data *data)
{
	if (data->threads)
	{
		free(data->threads);
		data->threads = NULL;
	}
}

void	cleanup(t_data *data)
{
	cleanup_philos(data);
	cleanup_forks(data);
	cleanup_threads(data);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->eat_count_mutex);
}
