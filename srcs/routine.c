/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:40:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/03 20:38:00 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *data)
{
	t_philo *current_philo = (t_philo *)data;
	t_table *table = current_philo -> table;

	pthread_mutex_lock(&table->table_mtx);
	table->philo_started++;
	pthread_mutex_unlock(&table->table_mtx);

	while (!(ft_get_int(&table->table_mtx, &table->start_simulation)))
		;
	pthread_mutex_lock(&current_philo->philo_mutex);
	current_philo->last_eaten = get_time();
	pthread_mutex_unlock(&current_philo->philo_mutex);

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


