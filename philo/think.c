/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:12:28 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/05 19:07:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	think(t_philo *philo)
{
	int	time;

	if (ft_get_int(&philo->table->table_mtx, &philo->table->end_simulation))
		return (0);
	write_state(philo, THINKING);
	time = philo->table->time_to_die - philo->table->time_to_eat
		- philo->table->time_to_sleep;
	if (time > 100)
	{
		ft_usleep(10, philo);
	}
	return (1);
}
