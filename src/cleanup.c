# include "../includes/philo.h"

void    destroy_mutex(t_data *data)
{
    int i;

    if (data->forks)
    {
        i = 0;
        while (i < data->nb_philos)
        {
            pthread_mutex_destroy(&data->forks[i]);
            i++;
        }
    }
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
    pthread_mutex_destroy(&data->meal_mutex);
}

void    cleanup_data(t_data *data)
{
    destroy_mutex(data);
    if (data->forks)
    {
        free(data->forks);
        data->forks = NULL;
    }
    if (data->philos)
    {
        free(data->philos);
        data->philos = NULL;
    }
}