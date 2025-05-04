/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:51:29 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/04 20:09:21 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	kill_philo(t_table *table, int i)
{
	pthread_mutex_lock(&table->write_mtx);
	ft_set_int(&table->table_mtx, &table->end_simulation, 1);
	print_time(table);
	printf("%d died\n", i + 1);
	pthread_mutex_unlock(&table->write_mtx);
	pthread_mutex_unlock(&table->philos[i].philo_mutex);
}

int	philo_timeout(t_table *table, int i)
{
	return (get_time() - table->philos[i].last_eaten >= table->time_to_die);
}

void	*monitor(void *arg)
{
	int		i;
	t_table	*table;

	table = arg;
	while (!ft_get_int(&table->table_mtx, &table->start_simulation))
		;
	while (!ft_get_int(&table->table_mtx, &table->end_simulation))
	{
		i = 0;
		while (i < table->philo_count)
		{
			pthread_mutex_lock(&table->philos[i].philo_mutex);
			if (table->philos[i].last_eaten == -1 || table->philos[i].full)
				;
			else if (philo_timeout(table, i))
			{
				kill_philo(table, i);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philos[i].philo_mutex);
			i++;
		}
	}
	return (NULL);
}

int	start_monitor(t_table *table)
{
	int	return_value;

	return_value = pthread_create(&table->monitor, NULL, monitor, table);
	if (return_value == EINVAL || return_value == EAGAIN
		|| return_value == EPERM)
	{
		printf("Error while creating thread monitor.\n");
		return (0);
	}
	return (1);
}
