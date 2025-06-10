# include "../includes/philo.h"

int is_space(int c)
{
    return (c == ' ' || c == '\t' || c == '\n'
    || c == '\v' || c == '\f' || c == '\r');
}

int is_digit(int c)
{
    return (c >= '0' && c <= '9');
}

int is_valide_number(const char *str)
{
    int i;

    if (!str || !*str)
        return (0);
    i = 0;
    while (is_space(str[i]))
        i++;
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
        return (0);
    if (!is_digit(str[i]))
        return (0);
    while (str[i])
    {
        if (!is_digit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

long    ft_atol(const char *str)
{
    long    res;
    long    sign;
    int     i;

    res = 0;
    sign = 1;
    i = 0;
    while (is_space(str[i]))
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (is_digit(str[i]))
    {
        if (res > (LONG_MAX - (str[i] - '0'))/10)
            return (-1);
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (sign * res);
}

int parse_args(int ac, char **av, t_data *data)
{
    int i;

    if (ac < 5 || ac > 6)
    {
        printf(ERR_ARGS);
        return (1);
    }
    i = 1;
    while (i < ac)
    {
        if (!is_valide_number(av[i]))
        {
            printf(ERR_NUMERIC);
            return (1);
        }
        i++;
    }
    data->nb_philos = (int)ft_atol(av[1]);
    data->time_to_die = ft_atol(av[2]);
    data->time_to_eat = ft_atol(av[3]);
    data->time_to_sleep = ft_atol(av[4]);
    data->nb_meals = -1;
    if (ac == 6)
        data->nb_meals = (int)ft_atol(av[5]);
    if (data->nb_philos < 1 || data->nb_philos > MAX_PHILOS)
    {
        printf(ERR_PHILO_COUNT);
        return (1);
    }
    if (data->time_to_die < MIN_TIME || data->time_to_eat < MIN_TIME
        || data->time_to_sleep < MIN_TIME)
    {
        printf(ERR_TIME_VALUES);
        return (1);
    }
    if (ac == 6 && data->nb_meals <= 0)
    {
        printf(ERR_MEALS_COUNT);
        return (1);
    }
    return (0);
}