/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:10:29 by asezgin           #+#    #+#             */
/*   Updated: 2025/06/25 13:10:29 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "phlio.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat = get_time();
	philo->eat_count++;
	print_status(philo, "is eating");
	pthread_mutex_unlock(&philo->eat_mutex);
	ft_usleep(philo->data->time_to_eat);
}

static void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_mutex);
		print_status(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
