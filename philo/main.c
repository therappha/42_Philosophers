/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:06:52 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/05 19:07:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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
			free(table -> philos);
			return (0);
		}
		table->philos[i].index = i;
		table->philos[i].table = table;
		table->philos[i].last_eaten = -1;
		table->philos[i].full = 0;
		table->philos[i].eaten = 0;
		assign_forks(table, &table->philos[i++], table->forks);
	}
	return (1);
}

void	create_threads(t_table *table)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = table->philos;
	while (i < table->philo_count)
	{
		if (!ft_thread_init(&philos[i].philo_thread, &philos[i]))
			printf("error in creating philo thread %d\n", i + 1);
		i++;
	}
}

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	start_monitor(table);
	ft_set_int(&table->table_mtx, &table->start_simulation, 1);
	while (i < table->philo_count)
	{
		pthread_join(table->philos[i].philo_thread, NULL);
		i++;
	}
	if (!ft_get_int(&table->table_mtx, &table->end_simulation))
		printf("All philosophers have eaten, simulation ended!\n");
	ft_set_int(&table->table_mtx, &table->end_simulation, 1);
	pthread_join(table->monitor, NULL);
}

int	main(int ac, char **av)
{
	t_table			table;

	if (ac != 5 && ac != 6)
		return (0);
	if (!table_input_init(ac, av, &table))
		return (0);
	if (!init_forks(&table))
	{
		free_table_mutex(&table);
		return (0);
	}
	if (!init_philos(&table))
	{
		free_table_mutex(&table);
		free_forks(&table);
		return (0);
	}
	create_threads(&table);
	while (ft_get_int(&table.table_mtx, &table.philo_started)
		!= table.philo_count)
		usleep(500);
	start_simulation(&table);
	free_all(&table);
	return (0);
}
