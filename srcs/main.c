/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:06:52 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/03 20:48:02 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	table_input_init(int ac, char **av, t_table *table)
{
	if (!ft_mutex_init(&table->table_mtx))
		return (0);
	if (!ft_mutex_init(&table->write_mtx))
		return (0);
	table -> start_simulation = 0;
	table -> end_simulation = 0;
	table -> philo_started = 0;
	table -> philo_count = ft_atoi(av[1]);
	table -> time_to_die = ft_atoi(av[2]);
	table -> time_to_eat = ft_atoi(av[3]);
	table -> time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table -> must_eat = ft_atoi(av[5]);
	else
		table -> must_eat = -1;
	//printf("input validated with sucess!\n");
	return (1);
}


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
			{
				pthread_mutex_destroy(&table->forks[j++].fork);
				printf("Error initing fork mutexes!\n");
			}
			return (0);
		}
		table->forks[i].fork_id = i;
		i++;
	}
	//printf("forks inited with sucess!\n");
	return (1);
}

void	assign_forks(t_table *table, t_philo *philo, t_fork *forks)
{

	if ((philo->index + 1) % 2 == 0)
	{
		philo->first_fork = &forks[philo->index];
		philo->second_fork = &forks[(philo->index + 1) % table->philo_count];
	}
	else
	{
		philo->first_fork = &forks[(philo->index + 1) % table->philo_count];
		philo->second_fork = &forks[philo->index];
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
		table->philos[i].last_eaten = -1;
		assign_forks(table, &table->philos[i], table->forks);
		i++;
	}
	//printf("All philo struct malloced and inited!\n\n");
	return (1);
}

void	create_threads(t_table *table, int philo_count)
{
	t_philo *philos = table->philos;

	for (int i = 0; i < philo_count; i++)
	{
		if (!ft_thread_init(&philos[i].philo_thread, &philos[i]))
		{
			for (int j = 0; j < i; j++);
				// free threads? this is just a concept here
		}
	}
}

int	main(int ac, char **av)
{
	t_table			table;
	int				philo_count;

	if (ac != 5 && ac != 6)
		return (0);
	if (!table_input_init(ac, av, &table))
		return (0);
	philo_count = table.philo_count;
	if (!init_forks(&table))
		return (0);
	if (!init_philos(&table))
	{
		//free forks
		return (0);
	}
	/*for (int i = 0; i < table.philo_count; i++)
	{
		printf("philo number %d has first_fork %p and second_fork %p assigned!\n\n", i + 1, &table.philos[i].first_fork->fork, &table.philos[i].second_fork->fork );
	}*/
	create_threads(&table, philo_count);
	while (ft_get_int(&table.table_mtx, &table.philo_started) != philo_count)
		;

	table.start_time = get_time();
	start_monitor(&table);
	ft_set_int(&table.table_mtx, &table.start_simulation, 1);
	for (int i = 0; i < philo_count; i++)
	{
		pthread_join(table.philos[i].philo_thread, NULL);
	}
	pthread_join(table.monitor, NULL);
	if (!table.end_simulation)
		printf("All philosophers have eaten, simulation ended!\n");
	//freeall
	return (0);
}
