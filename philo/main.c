#include <stdio.h>
#include "phlio.h"
#include <sys/time.h>
#include <stddef.h>
#include "stdlib.h"


int init_fork (t_simulation *sim)
{
    int index;

    index = 0;
    sim->forks = malloc(sim->number_of_philosopher * sizeof(pthread_mutex_t));
    if (!sim->forks)
        return (1);
    while (sim->number_of_philosopher > index)
    {
        if (pthread_mutex_init(&sim->forks[index], NULL))
        {
            free(sim->forks);
            return(1);
        }
        index++;
    }
    return (0);
}

int init_philos(t_simulation *sim)
{
    int index;

    index = 0;
    sim->philos = malloc(sim->number_of_philosopher * sizeof(t_philo));
    while (sim->number_of_philosopher > index)
    {
        sim->philos[index] = (t_philo) {
            .id = index + 1,
            .last_meal_time = get_current_time(),
            .sim = sim,
            .left_fork = sim->forks[index],
            .right_fork = sim->forks[index + 1], //TODO değişecek
        };
        if (pthread_mutex_init(&sim->philos[index].meal_lock, NULL))
        {
            free(sim->philos);
            return (1);
        }
        if (pthread_mutex_init(&sim->philos[index].eat_lock, NULL))
        {
            free(sim->philos);
            return (1);
        }
        index++;
    }
}

int init_simulation(t_simulation *sim, int argc, char **argv)
{
    int err;

    err = 0;
    *sim = (t_simulation) {
        .number_of_philosopher = safe_atoi(argv[1], &err),
        .time_to_die = safe_atoi(argv[2], &err),
        .time_to_eat = safe_atoi(argv[3], &err),
        .time_to_sleep = safe_atoi(argv[4], &err),
        .start_time = get_current_time()
    };
    if (argc == 6)
        sim->eat_count = safe_atoi(argv[5], &err);
    if (err)
        return (err);
    if (pthread_mutex_init(&sim->finish_mutex, NULL))
        return (err);
    if(init_fork(sim))
        return (1);
    if(init_philos(sim))
        return (1);
}

int start_philos(t_simulation *sim);

void start_simulation(t_simulation *sim);

int main(int argc, char *argv[])
{
    t_simulation    sim;

    if (!(argc == 5 || argc == 6))
        return (1);
    if (!init_simulation(&sim, argc, argv))
        /*XXX ensure that print err and exit*/
    start_simulation(&sim);
}