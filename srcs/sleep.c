/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:13:47 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/03 19:27:49 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	sleeping(t_philo *philo)
{
	if (ft_get_int(&philo->table->table_mtx, &philo->table->end_simulation))
		return (0);
	write_state(philo, SLEEPING);
	usleep(philo->table->time_to_sleep * 1000);
	return (1);
}
