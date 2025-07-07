/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:10:49 by asezgin           #+#    #+#             */
/*   Updated: 2025/06/25 13:10:49 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phlio.h"

static int	check_philo_death(t_philo *philo)
{
	long long	current_time;
	int			died;

	pthread_mutex_lock(&philo->eat_mutex);
	current_time = get_time();
	died = (current_time - philo->last_eat > philo->data->time_to_die);
	pthread_mutex_unlock(&philo->eat_mutex);
	return (died);
}

static int	check_all_philos_eaten(t_data *data)
{
	int	i;

	if (data->eat_count == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].eat_mutex);
		if (data->philos[i].eat_count < data->eat_count)
		{
			pthread_mutex_unlock(&data->philos[i].eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].eat_mutex);
		i++;
	}
	return (1);
}

static void	check_deaths(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (check_philo_death(&data->philos[i]))
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d died\n", get_time() - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->dead_mutex);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			return ;
		}
		i++;
	}
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	data->start = 1;
	while (1)
	{
		check_deaths(data);
		if (data->dead)
			return (NULL);
		if (check_all_philos_eaten(data))
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			return (NULL);
		}
	}
	return (NULL);
}

int	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->threads[i], NULL, philosopher_routine,
				&data->philos[i]))
		{
			free(data->threads);
			return (1);
		}
		i++;
	}
	return (0);
}
