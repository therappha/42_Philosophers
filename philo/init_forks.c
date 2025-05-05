/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:47:21 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/05 19:07:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	init_forks(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	table -> forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_count);
	if (!table -> forks)
		return (0);
	while (i < table -> philo_count)
	{
		if (!ft_mutex_init(&table->forks[i].fork))
		{
			while (j < i)
			{
				pthread_mutex_destroy(&table->forks[j++].fork);
				printf("Error initing fork mutexes!\n");
			}
			return (0);
		}
		table->forks[i].fork_id = i;
		i++;
	}
	return (1);
}

void	assign_forks(t_table *table, t_philo *philo, t_fork *forks)
{
	if ((philo->index + 1) % 2 == 0)
	{
		philo->first_fork = &forks[philo->index];
		philo->second_fork = &forks[(philo->index + 1) % table->philo_count];
	}
	else
	{
		philo->first_fork = &forks[(philo->index + 1) % table->philo_count];
		philo->second_fork = &forks[philo->index];
	}
}
