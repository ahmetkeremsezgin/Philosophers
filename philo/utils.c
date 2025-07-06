/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:10:57 by asezgin           #+#    #+#             */
/*   Updated: 2025/06/25 13:10:57 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phlio.h"

static void	print_message(t_philo *philo, char *status)
{
	printf("%lld %d %s\n", get_time() - philo->data->start_time,
		philo->id, status);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (!philo->data->dead)
		print_message(philo, status);
	pthread_mutex_unlock(&philo->data->dead_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}


int	create_threads(t_data *data)
{
	data->threads = malloc(data->num_philos * sizeof(pthread_t));
	if (!data->threads)
		return (1);
	if (create_philosopher_threads(data))
		return (1);
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data))
	{
		free(data->threads);
		return (1);
	}
	join_threads(data);
	return (0);
}

void	join_threads(t_data *data)
{
	int	i;

	pthread_join(data->monitor_thread, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}
