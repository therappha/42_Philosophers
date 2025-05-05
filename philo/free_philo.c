/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:14:25 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/05 19:07:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	free_table_mutex(t_table *table)
{
	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->write_mtx);
}

void	free_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		i++;
	}
	free(table->forks);
}

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	free_table_mutex(table);
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
		i++;
	}
	free_forks(table);
	free(table->philos);
}
