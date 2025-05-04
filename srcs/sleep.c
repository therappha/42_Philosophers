/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:13:47 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/04 21:40:05 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	sleeping(t_philo *philo)
{
	int	i;

	long long	start_time;

	i = 0;
	if (ft_get_int(&philo->table->table_mtx, &philo->table->end_simulation))
		return (0);
	write_state(philo, SLEEPING);

	start_time = get_time();
	while (!ft_get_int(&philo->table->table_mtx, &philo->table->end_simulation))
	{
		usleep(1000);
		if (get_time() - start_time >= philo->table->time_to_sleep)
			break;
		i++;
	}
	if (ft_get_int(&philo->table->table_mtx, &philo->table->end_simulation))
		return (0);
	return (1);
}
