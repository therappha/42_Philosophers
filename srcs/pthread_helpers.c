/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:19:13 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/04 21:56:38 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_mutex_init(t_mtx *mutex)
{
	int	return_value;

	return_value = pthread_mutex_init(mutex, NULL);
	if (return_value == EINVAL)
		printf("Invalid value was passed for the mutex attributes.\n");
	else if (return_value == ENOMEM)
		printf("Insufficient memory to initialize the mutex.\n" );
	if (return_value == 0)
		return (1);
	else
		return (0);
}

int	ft_thread_init(pthread_t *thread, t_philo *arg)
{
	int	return_value;

	return_value = pthread_create(thread, NULL, routine, arg);
	if (return_value == EINVAL || return_value == EAGAIN
		|| return_value == EPERM)
	{
		printf("Error while creating philo thread.\n");
		return (0);
	}
	return (1);
}

void	ft_usleep(int time, t_philo *philo)
{
	long long	start_time;
	int			i;

	i = 0;
	start_time = get_time();
	while (!ft_get_int(&philo->table->table_mtx, &philo->table->end_simulation))
	{
		usleep(1000);
		if (get_time() - start_time >= (long long)time)
			break ;
		i++;
	}
}
