/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:32:04 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/03 19:37:49 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

struct					s_table;
typedef struct s_table	t_table;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	GET_FORK,
	RELEASED,
} t_state;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				index;
	long long		last_eaten;
	int				eated;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_table			*table;
	pthread_mutex_t	philo_mutex;
}	t_philo;

typedef struct s_table
{
	int				philo_count;
	int				philo_started;
	int				start_simulation;
	int				end_simulation;
	long long		start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	write_mtx;
	pthread_mutex_t	table_mtx;
}	t_table;

//utils
int			ft_atoi(char *str);
int			ft_mutex_init(pthread_mutex_t *mutex);
int			ft_get_int(pthread_mutex_t *mutex, int *variable);
void		ft_set_int(pthread_mutex_t *mutex, int *variable, int newvalue);
void		ft_set_ll(pthread_mutex_t *mutex, long long *variable, long long newvalue);
long long	ft_get_ll(pthread_mutex_t *mutex, long long *variable);
int			ft_thread_init(pthread_t *thread, t_philo *arg);
void		print_time(t_table	*table);
void		write_state(t_philo *philo, t_state state);
void		*routine(void *data);
long long	get_time(void);


int	sleeping(t_philo *philo);
int	think(t_philo *philo);
int	eating(t_philo *philo);

//debug purposes
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"

#endif
