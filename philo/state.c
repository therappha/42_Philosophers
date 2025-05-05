/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:08:51 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/05 19:07:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	print_get_fork(t_philo *philo)
{
	print_time(philo->table);
	printf("%d has taken a fork\n", philo->index + 1);
}

void	print_eating(t_philo *philo)
{
	print_time(philo->table);
	printf("%d is eating\n", philo->index + 1);
}

void	print_sleeping(t_philo *philo)
{
	print_time(philo->table);
	printf("%d is sleeping\n", philo->index + 1);
}

void	print_thinking(t_philo *philo)
{
	print_time(philo->table);
	printf("%d is thinking\n", philo->index + 1);
}

void	write_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->table->write_mtx);
	if (ft_get_int(&philo->table->table_mtx, &philo->table->end_simulation))
	{
		pthread_mutex_unlock(&philo->table->write_mtx);
		return ;
	}
	if (state == GET_FORK)
		print_get_fork(philo);
	else if (state == EATING)
		print_eating(philo);
	else if (state == SLEEPING)
		print_sleeping(philo);
	else if (state == THINKING)
		print_thinking(philo);
	pthread_mutex_unlock(&philo->table->write_mtx);
}
