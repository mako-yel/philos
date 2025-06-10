# include "../includes/philo.h"

void    print_action(t_philo *philo, e_action action)
{   
    long    timestamp;

    pthread_mutex_lock(&philo->data->print_mutex);
    if (!is_simulation_over(philo->data) || action == DIED)
    {
        timestamp = get_time() - philo->data->start_time;
        if (action == TAKE_FORK)
            printf(MSG_FORK, timestamp, philo->id);
        else if (action == EATING)
            printf(MSG_EAT, timestamp, philo->id);
        else if (action == SLEEPING)
            printf(MSG_SLEEP, timestamp, philo->id);
        else if (action == THINKING)
            printf(MSG_THINK, timestamp, philo->id);
        else if (action == DIED)
            printf(MSG_DEATH, timestamp, philo->id);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void    take_forks(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    if (philo->data->nb_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, TAKE_FORK);
        return ;
    }
    if (philo->left_fork < philo->right_fork)
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
    else
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
    pthread_mutex_lock(first_fork);
    print_action(philo, TAKE_FORK);
    pthread_mutex_lock(second_fork);
    print_action(philo, TAKE_FORK);
}

void    eat(t_philo *philo)
{
    print_action(philo, EATING);
    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&philo->data->meal_mutex);
    ft_usleep(philo->data->time_to_eat);
    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->meal_mutex);
    if (philo->data->nb_philos > 1)
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
    }
    else
        pthread_mutex_unlock(philo->left_fork);
}

void    sleep_and_think(t_philo *philo)
{
    print_action(philo, SLEEPING);
    ft_usleep(philo->data->time_to_sleep);
    print_action(philo, THINKING);
}