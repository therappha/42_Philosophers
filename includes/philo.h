/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:32:04 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/04 20:19:55 by rafaelfe         ###   ########.fr       */
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
# include <limits.h>

struct					s_table;
typedef struct s_table	t_table;

typedef	pthread_mutex_t t_mtx;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	GET_FORK,
} t_state;

typedef struct s_fork
{
	t_mtx	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				index;
	long long		last_eaten;
	int				eaten;
	int				full;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_table			*table;
	t_mtx	philo_mutex;
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
	t_mtx	write_mtx;
	t_mtx	table_mtx;
	pthread_t		monitor;
}	t_table;


long long	ft_atoll(char *str);
int			ft_mutex_init(t_mtx *mutex);
int			init_forks(t_table *table);
void		assign_forks(t_table *table, t_philo *philo, t_fork *forks);

void		print_time(t_table	*table);
void		write_state(t_philo *philo, t_state state);

int			start_monitor(t_table *table);
long long	get_time(void);

void		*routine(void *data);
int	sleeping(t_philo *philo);
int	think(t_philo *philo);
int	eating(t_philo *philo);

//getters_setters
int			ft_get_int(t_mtx *mutex, int *variable);
void		ft_set_int(t_mtx *mutex, int *variable, int newvalue);
void		ft_set_ll(t_mtx *mutex, long long *variable, long long newvalue);
long long	ft_get_ll(t_mtx *mutex, long long *variable);
int			ft_thread_init(pthread_t *thread, t_philo *arg);
#endif
