# include "../includes/philo.h"

int is_simulation_over(t_data *data)
{
    int res;

    pthread_mutex_lock(&data->death_mutex);
    res = data->simulation_stop;
    pthread_mutex_unlock(&data->death_mutex);
    return (res);
}

int check_death(t_philo *philo)
{
    long    current_time;
    long    time_since_last_meal;

    pthread_mutex_lock(&philo->data->meal_mutex);
    current_time = get_time();
    time_since_last_meal = current_time - philo->last_meal_time;
    pthread_mutex_unlock(&philo->data->meal_mutex);
    if (time_since_last_meal >= philo->data->time_to_die)
        return (1);
    return (0);
}

void    set_simulation_stop(t_data *data)
{
    pthread_mutex_lock(&data->death_mutex);
    data->simulation_stop = 1;
    pthread_mutex_unlock(&data->death_mutex);
}