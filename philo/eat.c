/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:43:53 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/05 19:07:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	get_first_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_state(philo, GET_FORK);
}

void	get_second_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->second_fork->fork);
	write_state(philo, GET_FORK);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

int	eating(t_philo *philo)
{
	if ((philo->full))
		return (0);
	if (ft_get_int(&philo->table->table_mtx, &philo->table->end_simulation))
		return (0);
	get_first_fork(philo);
	get_second_fork(philo);
	pthread_mutex_lock(&philo->philo_mutex);
	write_state(philo, EATING);
	philo->last_eaten = get_time();
	philo->eaten++;
	if (philo->eaten == philo->table->must_eat)
		philo->full = 1;
	pthread_mutex_unlock(&philo->philo_mutex);
	ft_usleep(philo->table->time_to_eat, philo);
	release_forks(philo);
	if (ft_get_int(&philo->table->table_mtx, &philo->table->end_simulation))
		return (0);
	return (1);
}
