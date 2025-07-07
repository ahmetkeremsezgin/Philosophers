/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phlio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:10:43 by asezgin           #+#    #+#             */
/*   Updated: 2025/06/25 13:10:43 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHLIO_H
# define PHLIO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_mutex;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	long long		start_time;
	int				dead;
	int				start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_t		monitor_thread;
}					t_data;

int					ft_atoi(const char *str);
long long			get_time(void);
void				ft_usleep(long long time);
void				print_status(t_philo *philo, char *status);
int					init_data(t_data *data, int argc, char **argv);
int					create_threads(t_data *data);
void				*philosopher_routine(void *arg);
void				*monitor_routine(void *arg);
void				cleanup(t_data *data);
void				join_threads(t_data *data);
int					create_philosopher_threads(t_data *data);
#endif
