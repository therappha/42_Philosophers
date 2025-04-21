/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:19:13 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/21 21:42:18 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_mutex_init(pthread_mutex_t *mutex)
{
	int	return_value;

	return_value = pthread_mutex_init(mutex, NULL);
	if (return_value == EINVAL)
		printf(RED"Invalid value was passed for the mutex attributes.\n"RESET);
	else if (return_value == ENOMEM)
		printf(RED"Insufficient memory to initialize the mutex.\n" RESET);
	if (return_value == 0)
		return (1);
	else
		return (0);
}

int	ft_get_int(pthread_mutex_t *mutex, int *variable)
{
	int get;
	pthread_mutex_lock(mutex);
	get = *variable;
	pthread_mutex_unlock(mutex);
	return (get);
}
