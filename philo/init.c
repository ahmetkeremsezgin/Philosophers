/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:10:06 by asezgin           #+#    #+#             */
/*   Updated: 2025/06/25 13:10:06 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phlio.h"
#include <stdlib.h>

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->start_mutex, NULL))
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (1);
	}
	if (pthread_mutex_init(&data->dead_mutex, NULL))
	{
		pthread_mutex_destroy(&data->start_mutex);
		pthread_mutex_destroy(&data->print_mutex);
		return (1);
	}
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(data->num_philos * sizeof(t_philo));
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].eat_mutex, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philos[i].eat_mutex);
			free(data->philos);
			return (1);
		}
		i++;
	}
	return (0);
}

void	start_mutex_handele(t_data *data)
{
	pthread_mutex_lock(&data->start_mutex);
	data->start = 0;
	pthread_mutex_unlock(&data->start_mutex);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->eat_count = -1;
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	data->start_time = get_time();
	data->dead = 0;
	if (init_mutexes(data))
		return (1);
	start_mutex_handele(data);
	if (init_forks(data))
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->dead_mutex);
		return (1);
	}
	if (init_philos(data))
	{
		cleanup(data);
		return (1);
	}
	return (0);
}
