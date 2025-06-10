# include "../includes/philo.h"

int main(int ac, char **av)
{
    t_data  data;

    if (parse_args(ac, av, &data) != 0)
        return (1);
    if (init_data(&data) != 0)
    {
        cleanup_data(&data);
        return (1); 
    }
    if (start_simulation(&data) != 0)
    {
        cleanup_data(&data);
        return (1);
    }
    supervise_philosophers(&data);
    cleanup_data(&data);
    return (0);
}