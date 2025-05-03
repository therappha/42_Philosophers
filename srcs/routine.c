/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:40:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/03 19:29:42 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *routine(void *data)
{
	t_philo *current_philo = (t_philo *)data;
	t_table *table = current_philo -> table;

	pthread_mutex_lock(&table->table_mtx);
	table->philo_started++;
	pthread_mutex_unlock(&table->table_mtx);

	while (!(ft_get_int(&table->table_mtx, &table->start_simulation)))
		;
	if (table->philo_count == 1)
	{
		return NULL;
	}
	while (!(ft_get_int(&table->table_mtx, &table->end_simulation)))
	{
		if (!eating(current_philo))
			return (NULL);
		if (!think(current_philo))
			return (NULL);
		if (!sleeping(current_philo))
			return (NULL);
	}
	return (NULL);
}
