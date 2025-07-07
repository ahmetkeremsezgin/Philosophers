/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:09:58 by asezgin           #+#    #+#             */
/*   Updated: 2025/06/25 13:09:58 by asezgin          ###   ########.fr       */
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
}
