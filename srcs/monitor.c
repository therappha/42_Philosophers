/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:51:29 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/03 20:49:29 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_routine(void *arg)
{
	int	i;

	t_table *table;

	table = arg;
	while (!ft_get_int(&table->table_mtx, &table->start_simulation))
		;
	while (!ft_get_int(&table->table_mtx, &table->end_simulation))
	{
		i = 0;
		while (i < table->philo_count)
		{
			pthread_mutex_lock(&table->philos[i].philo_mutex);
			if (table->philos[i].last_eaten == -1 || (table->must_eat != -1 && table->philos[i].eaten == table->must_eat))
			{
				pthread_mutex_unlock(&table->philos[i].philo_mutex);
				i++;
				continue ;
			}
			if (get_time() - table->philos[i].last_eaten >= table->time_to_die)
			{
				pthread_mutex_lock(&table->write_mtx);
				ft_set_int(&table->table_mtx, &table->end_simulation, 1);
				print_time(table);
				printf("%d died\n", i + 1);
				pthread_mutex_unlock(&table->write_mtx);
				pthread_mutex_unlock(&table->philos[i].philo_mutex);
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
	pthread_create(&table->monitor, NULL, monitor_routine, table);

	return (1);
}


