#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>

typedef struct  s_simulation t_simulation;

typedef struct  s_philo
{
	int				id;
	long			last_meal_time;
	int				eat_count;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t eat_lock;
	t_simulation	*sim;
} t_philo;

typedef struct  s_simulation
{
	int				number_of_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	long			start_time;
	int				is_over;
	pthread_mutex_t finish_mutex;
	t_philo 		*philos;
	pthread_mutex_t *forks;
} t_simulation;


int safe_atoi(char *input, int *err);
unsigned long get_current_time();

#endif
