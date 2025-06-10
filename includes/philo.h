# ifndef PHILO_H
# define PHILO_H

// Standard libraries
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>

/* color macros */
# define RED "\033[0;31m" // "/033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"  
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

/* Message errors */
# define ERR_ARGS RED "Error: Invalid number of arguments\n"RESET\
"Usage: ./philo number_of_philos time_to_die time_to_eat"\
"time_to_sleep [number_of_times_each_philo_must_eat]\n"
# define ERR_PHILO_COUNT RED "Error: Number of philos must be between 0-200\n"RESET
# define ERR_TIME_VALUES RED "Error: Time values must be positive integers (> 0)\n"RESET
# define ERR_NUMERIC RED "Error: All args must be numeric\n"RESET
# define ERR_MEALS_COUNT RED "Error: Number of meals must be a positive integer\n"RESET
# define ERR_MALLOC RED "Error: Memory allocation failed\n"RESET
# define ERR_MUTEX RED "Error: Mutex initialization failed\n"RESET
# define ERR_THREAD RED "Error: Thread creation failed\n"RESET

/* Action message */
# define MSG_FORK CYAN "%ld %d has taken a fork\n"RESET
# define MSG_EAT GREEN "%ld %d is eating\n"RESET
# define MSG_SLEEP BLUE "%ld %d is sleeping\n"RESET
# define MSG_THINK YELLOW "%ld %d is thinking\n"RESET
# define MSG_DEATH RED "%ld %d died\n"RESET


/* Enums */
typedef enum s_action
{
    TAKE_FORK,
    EATING,
    SLEEPING,
    THINKING,
    DIED
}   e_action;

/* Structures */
typedef struct s_data t_data;


typedef struct s_philo
{
    int id; 
    int meals_eaten;
    long    last_meal_time;
    pthread_t   thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data  *data;
}   t_philo;

typedef struct s_data
{
    int     nb_philos;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    int     nb_meals;
    long    start_time;
    int     simulation_stop;
    int     philos_full;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    pthread_mutex_t meal_mutex;
    t_philo *philos;
}   t_data;

/* Constants */
# define MAX_PHILOS 200
# define MIN_TIME 60


/* Parsing functions */
int parse_args(int ac, char **av, t_data *data);
int is_space(int c);
int is_digit(int c);
int is_valide_number(const char *str);
long    ft_atol(const char *str);

/* Init  */
int init_mutex(t_data *data);
int init_philos(t_data *data);
int init_data(t_data *data);

/* Cleaning up */
void    cleanup_data(t_data *data);
void    destroy_mutex(t_data *data);

/* Get time */
long    get_time(void);
void    ft_usleep(long time_to_sleep_ms);

/* Simulation */
void    *philo_routine(void *arg);
int start_simulation(t_data *data);
void    supervise_philosophers(t_data *data);

/* Actions */
void    print_action(t_philo *philo, e_action action);
void    take_forks(t_philo *philo);
void    eat(t_philo *philo);
void    sleep_and_think(t_philo *philo);

/* Utils */
int is_simulation_over(t_data *data);
int check_death(t_philo *philo);
void    set_simulation_stop(t_data *data);


#endif
