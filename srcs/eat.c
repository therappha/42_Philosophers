/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:43:53 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/03 19:38:58 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	write_state(philo, RELEASED);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

int	eating(t_philo *philo)
{
	if (ft_get_int(&philo->table->table_mtx, &philo->table->end_simulation) ||
		philo->eated == philo->table->must_eat)
			return (0);
	get_first_fork(philo);
	get_second_fork(philo);
	write_state(philo, EATING);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_eaten = get_time();
	philo->eated++;
	pthread_mutex_unlock(&philo->philo_mutex);
	usleep(philo->table->time_to_eat * 1000);
	release_forks(philo);
	return (1);
}
