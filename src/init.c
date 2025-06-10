#include "philo.h"

int init_mutex(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
    if (!data->forks)
    {
        printf(ERR_MALLOC);
        return (1);
    }
    i = 0;
    while (i < data->nb_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            printf(ERR_MUTEX);
            return (1);
        }
        i++;
    }
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0 || pthread_mutex_init(&data->death_mutex, NULL) != 0
    || pthread_mutex_init(&data->meal_mutex, NULL) != 0)
    {
        printf(ERR_MUTEX);
        return (1);
    }
    return (0);
}

int init_philos(t_data *data)
{
    int i;

    data->philos = malloc(sizeof(t_philo) * data->nb_philos);
    if (!data->philos)
    {
        printf(ERR_MALLOC);
        return (1);
    }
    i = 0;
    while (i < data->nb_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = 0;
        data->philos[i].data = data;
        data->philos[i].left_fork = &data->forks[i];
        if (data->nb_philos > 1)
            data->philos[i].right_fork = &data->forks[(i + 1)
            % data->nb_philos];
        else 
            data->philos[i].right_fork = NULL;
        i++;
    }
    return (0);
}

int init_data(t_data *data)
{
    data->start_time = get_time();
    data->simulation_stop = 0;
    data->philos_full = 0;
    if (init_mutex(data) != 0)
        return (1);
    if (init_philos(data) != 0)
        return (1);
    return (0);
}