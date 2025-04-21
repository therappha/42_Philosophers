#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>

typedef enum e_state
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
} t_state;

typedef	struct s_times
{
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_times;

typedef struct s_philo
{
	int		index;
	t_times	times;
	int		last_eaten;
	int		eated;

}	t_philo;

//utils
int	ft_atoi(char *str);


#endif
