/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:06:52 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/21 21:44:52 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	table_input_init(int ac, char **av, t_table *table)
{
	if (!ft_mutex_init(&table->table_mtx))
		return (0);
	table -> start_simulation = 0;
	table -> end_simulation = 0;
	table -> philo_count = ft_atoi(av[1]);
	table -> time_to_die = ft_atoi(av[2]);
	table -> time_to_eat = ft_atoi(av[3]);
	table -> time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table -> must_eat = ft_atoi(av[5]);
	else
		table -> must_eat = -1;
	printf(GREEN"input validated with sucess!\n"RESET);
	return (1);
}
/*	gettimeofday(&tv, NULL);
	long	launch_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	long current_time;
	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - launch_time;
*/

int	init_forks(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	table -> forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_count);
	if (!table -> forks)
		return (0);
	while (i < table -> philo_count)
	{
		if (!ft_mutex_init(&table->forks[i].fork))
		{
			while (j < i)
				pthread_mutex_destroy(&table->forks[j++].fork);
			return (0);
		}
		table->forks[i].fork_id = i;
		i++;
	}
	printf(GREEN "forks inited with sucess!\n" RESET);
	return (1);
}

void	assign_forks(t_table *table, t_philo *philo, t_fork *forks)
{

	if ((philo->index + 1) % 2 == 0)
	{
		philo->first_fork = forks[philo->index];
		philo->second_fork = forks[(philo->index + 1) % table->philo_count];
	}
	else
	{
		philo->first_fork = forks[(philo->index + 1) % table->philo_count];
		philo->second_fork = forks[philo->index];
	}
}

int	init_philos(t_table *table)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	table -> philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (!table -> philos)
		return (0);
	while (i < table -> philo_count)
	{
		if (!ft_mutex_init(&table->philos[i].philo_mutex))
		{
			while (j < i)
				pthread_mutex_destroy(&table->philos[j++].philo_mutex);
			return (0);
		}
		table->philos[i].index = i;
		table->philos[i].table = table;
		assign_forks(table, &table->philos[i], table->forks);
		i++;
	}
	printf(GREEN"All philo struct malloced and inited!\n"RESET);
	return (1);
}

void *routine(void *data)
{
	t_philo *current_philo = (t_philo *)data;
	t_table *table = current_philo -> table;

	printf(YELLOW"philosoper %d is waiting!\n"RESET, current_philo->index+1);
	while (!(ft_get_int(&table->table_mtx, &table->start_simulation)))
		;
	printf(GREEN"philosoper %d has started!\n"RESET, current_philo->index+1);

	if (table->philo_count == 1)
	{
		//wait for death;  // fake grab fork, wait inevitable fate
		return (NULL);
	}
	while (!(ft_get_int(&table->table_mtx, &table->end_simulation)))
	{
		//eat(current_philo);
		//think(current_philo);
		//sleep(current_philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table			table;

	if (ac != 5 && ac != 6)
		return (0);
	if (!table_input_init(ac, av, &table))
		return (0);
	if (!init_forks(&table))
		return (0);
	if (!init_philos(&table))
	{
		//free forks
		return (0);
	}
	for (int i = 0; i < table.philo_count; i++)
	{
		printf(YELLOW"philo number %d has first_fork %d and second_fork %d assigned!\n"RED, i + 1, table.philos[i].first_fork.fork_id, table.philos[i].second_fork.fork_id);
	}
	//init monitor
	//start_simulation;
	//freeall
	return (0);
}
