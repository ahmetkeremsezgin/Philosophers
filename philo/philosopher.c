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

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_mutex);

	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
}

static void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo;
    int think_time;

    philo = (t_philo *)arg;

    // start değişkenini mutex ile koruyarak kontrol ediyoruz
    while (1)
    {
        pthread_mutex_lock(&philo->data->start_mutex);
        int started = philo->data->start;
        pthread_mutex_unlock(&philo->data->start_mutex);
        if (started)
            break;
        usleep(100);
    }

    while (1)
    {
        if (philo->data->num_philos == 1)
        {
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken a fork");
            ft_usleep(philo->data->time_to_die);
            pthread_mutex_unlock(philo->left_fork);
            return (NULL);
        }

        pthread_mutex_lock(&philo->data->dead_mutex);
        if (philo->data->dead)
        {
            pthread_mutex_unlock(&philo->data->dead_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->dead_mutex);

        take_forks(philo);
        eat(philo);
        release_forks(philo);
        philo_sleep(philo);
        print_status(philo, "is thinking");

        think_time = (philo->data->time_to_die - (philo->data->time_to_sleep + philo->data->time_to_eat)) / 2;
        if (think_time > 0)
            ft_usleep(think_time);
    }
    return (NULL);
}

