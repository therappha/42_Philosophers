/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:07:59 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/04 21:11:03 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_is_numeric(char *num_str)
{
	int			i;

	i = 0;
	if (!num_str || !*num_str)
		return (0);
	if (num_str[i] == '-' || num_str[i] == '+')
		i++;
	while (num_str[i])
	{
		if (num_str[i] < '0' || num_str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	get_input(char **av, t_table *table)
{
	long long	philo_count;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;

	philo_count = ft_atoll(av[1]);
	time_to_die = ft_atoll(av[2]);
	time_to_eat = ft_atoll(av[3]);
	time_to_sleep = ft_atoll(av[4]);
	if (philo_count > INT_MAX || philo_count < 1)
		return (0);
	if (time_to_die > INT_MAX || time_to_die < 0)
		return (0);
	if (time_to_eat > INT_MAX || time_to_eat < 0)
		return (0);
	if (time_to_sleep > INT_MAX || time_to_sleep < 0)
		return (0);
	table->philo_count = philo_count;
	table->time_to_die = time_to_die;
	table->time_to_eat = time_to_eat;
	table->time_to_sleep = time_to_sleep;
	return (1);
}

int	valid_input(int ac, char **av, t_table *table)
{
	long long	must_eat;
	int			i;

	i = 1;
	while (i < ac)
	{
		if (!ft_is_numeric(av[i]))
			return (0);
		i++;
	}
	if (!get_input(av, table))
		return (0);
	if (ac == 6)
	{
		must_eat = ft_atoll(av[5]);
		if (must_eat > INT_MAX || must_eat < 0)
			return (0);
		table->must_eat = must_eat;
	}
	return (1);
}

int	table_input_init(int ac, char **av, t_table *table)
{
	if (!valid_input(ac, av, table))
		return (0);
	table -> start_simulation = 0;
	table -> philos = NULL;
	table -> end_simulation = 0;
	table -> philo_started = 0;
	if (!ft_mutex_init(&table->table_mtx))
		return (0);
	if (!ft_mutex_init(&table->write_mtx))
	{
		pthread_mutex_destroy(&table->table_mtx);
		return (0);
	}
	return (1);
}
