/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:39:13 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/04 20:09:44 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_get_int(t_mtx *mutex, int *variable)
{
	int	get;

	pthread_mutex_lock(mutex);
	get = *variable;
	pthread_mutex_unlock(mutex);
	return (get);
}

void	ft_set_int(t_mtx *mutex, int *variable, int newvalue)
{
	pthread_mutex_lock(mutex);
	*variable = newvalue;
	pthread_mutex_unlock(mutex);
}

void	ft_set_ll(t_mtx *mutex, long long *variable, long long newvalue)
{
	pthread_mutex_lock(mutex);
	*variable = newvalue;
	pthread_mutex_unlock(mutex);
}

long long	ft_get_ll(t_mtx *mutex, long long *variable)
{
	long long	value;

	pthread_mutex_lock(mutex);
	value = *variable;
	pthread_mutex_unlock(mutex);
	return (value);
}
