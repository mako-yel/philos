# include "../includes/philo.h"

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->data->nb_philos == 1)
    {
        print_action(philo, TAKE_FORK);
        ft_usleep(philo->data->time_to_die);
        print_action(philo, DIED);
        return (NULL);
    }
    while (!is_simulation_over(philo->data))
    {
        take_forks(philo);
        eat(philo);
        sleep_and_think(philo);
    }
    return (NULL);
}

int start_simulation(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philos)
    {
        data->philos[i].last_meal_time = get_time();
        if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
        {
            printf(ERR_THREAD);
            return (1);
        }
        i++;
    }
    return (0);
}

void    supervise_philosophers(t_data *data)
{
    int i;
    int all_ate_enough;

    while (!is_simulation_over(data))
    {
        i = 0;
        all_ate_enough = 1;
        while ( i < data->nb_philos)
        {
            if (check_death(&data->philos[i]))
            {
                print_action(&data->philos[i], DIED);
                set_simulation_stop(data);
                break ;
            }
            pthread_mutex_lock(&data->meal_mutex);
            if (data->nb_meals > 0 && data->philos[i].meals_eaten < data->nb_meals)
                all_ate_enough = 0;
            pthread_mutex_unlock(&data->meal_mutex);
            i++;
        }
        if (data->nb_meals > 0 && all_ate_enough && !is_simulation_over(data))
        {
            pthread_mutex_lock(&data->death_mutex);
            data->philos_full = 1;
            pthread_mutex_unlock(&data->death_mutex);
            // printf("meals eaten %d\n", data->philos->meals_eaten);
            set_simulation_stop(data);
        }
        ft_usleep(1);
    }
    i = 0;
    while (i < data->nb_philos)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }    
}