/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:40:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/05 19:07:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	lone_routine(t_table *table, t_philo *philo)
{
	if (table->philo_count == 1)
	{
		write_state(philo, GET_FORK);
		ft_usleep(table->time_to_die, philo);
		return (1);
	}
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo ->table;
	pthread_mutex_lock(&table->table_mtx);
	table->philo_started++;
	pthread_mutex_unlock(&table->table_mtx);
	while (!(ft_get_int(&table->table_mtx, &table->start_simulation)))
		usleep(100);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_eaten = get_time();
	pthread_mutex_unlock(&philo->philo_mutex);
	if (lone_routine(table, philo))
		return (NULL);
	while (!(ft_get_int(&table->table_mtx, &table->end_simulation)))
	{
		if (!eating(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
		if (!think(philo))
			return (NULL);
	}
	return (NULL);
}
