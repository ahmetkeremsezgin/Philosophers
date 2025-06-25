/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42 <42@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42                #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by 42               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phlio.h"

static int	check_philo_death(t_philo *philo)
{
	long long	current_time;

	pthread_mutex_lock(&philo->eat_mutex);
	current_time = get_time();
	if (current_time - philo->last_eat > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_mutex);
	return (0);
}

static int	check_all_philos_eaten(t_data *data)
{
	int	i;

	if (data->eat_count == -1)
		return (0);
	pthread_mutex_lock(&data->eat_count_mutex);
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].eat_count < data->eat_count)
		{
			pthread_mutex_unlock(&data->eat_count_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&data->eat_count_mutex);
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
		usleep(1000);
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
