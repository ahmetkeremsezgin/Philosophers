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

static void	handle_forks(t_philo *philo, int take)
{
	if (take)
	{
		if (philo->id % 2 == 0)
			usleep(100);
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
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_mutex);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
}

static void	handle_single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philosopher_cycle(t_philo *philo)
{
	int	think_time;

	handle_forks(philo, 1);
	eat(philo);
	handle_forks(philo, 0);
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	print_status(philo, "is thinking");
	think_time = (philo->data->time_to_die - (philo->data->time_to_sleep
				+ philo->data->time_to_eat)) / 2;
	if (think_time > 0)
		ft_usleep(think_time);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->start)
		usleep(100);
	while (1)
	{
		if (philo->data->num_philos == 1)
		{
			handle_single_philosopher(philo);
			return (NULL);
		}
		if (philo->data->dead)
			break ;
		philosopher_cycle(philo);
	}
	return (NULL);
}
