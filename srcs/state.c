/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:08:51 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/03 20:38:00 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



void	write_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->table->write_mtx);
	if (ft_get_int(&philo->table->table_mtx, &philo->table->end_simulation))
	{
		pthread_mutex_unlock(&philo->table->write_mtx);
		return ;
	}

	if (state == GET_FORK)
	{
		print_time(philo->table);
		printf("%d has taken a fork\n", philo->index + 1);
	}
	else if (state == EATING)
	{
		print_time(philo->table);
		printf("%d is eating\n", philo->index + 1);
	}
	else if (state == SLEEPING)
	{
		print_time(philo->table);
		printf("%d is sleeping\n", philo->index + 1);
	}
	else if (state == THINKING)
	{
		print_time(philo->table);
		printf("%d is thinking\n", philo->index + 1);
	}
	else if (state == RELEASED)
	{
		print_time(philo->table);
		printf("%d released the forks!\n", philo->index + 1);
	}
	pthread_mutex_unlock(&philo->table->write_mtx);
}




/*
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/
