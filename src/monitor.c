/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:55:05 by bortakuz          #+#    #+#             */
/*   Updated: 2023/09/17 17:56:17 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <stdio.h>

static void	philo_exit(t_philosophers *philo, int lock)
{
	int	i;

	i = -1;
	if (lock == 0)
		pthread_mutex_lock(&philo->data->print);
	while (i++, i < philo[0].data->number_of_philo)
	{
		philo[i].is_dead = 1;
	}
	pthread_mutex_unlock(&philo->data->print);
	i = -1;
	while (i++, i < philo[0].data->number_of_philo)
	{
		pthread_mutex_destroy(&philo[i].data->forks[i]);
	}
	pthread_mutex_destroy(&philo->data->print);
	free(philo[0].data->forks);
	free(philo);
	exit(0);
}

static void	death(t_philosophers *philo, int i)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %d philo dead\n", get_time() - philo[0].data->start, i + 1);
	philo_exit(philo, 1);
}

void	*monitor(void *new_data)
{
	t_philosophers	*philo;
	t_data			*data;
	int				i;
	int				stop;

	philo = *(t_philosophers **)(new_data);
	data = philo[0].data;
	data->start = get_time();
	while (1)
	{
		ft_usleep(1);
		i = -1;
		stop = 1;
		while (i++, i < data->number_of_philo)
		{
			philo[i].remain_death_time--;
			if (data->total_meal == -1 || (data->total_eaten_meal
					/ data->number_of_philo) < data->total_meal)
				stop = 0;
			if (philo[i].remain_death_time < 0)
				death(philo, i);
		}
		if (stop == 1)
			philo_exit(philo, 0);
	}
}
