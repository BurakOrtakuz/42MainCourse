/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:28:02 by bortakuz          #+#    #+#             */
/*   Updated: 2023/09/17 17:55:10 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <stdio.h>

static void	print_massage(t_philosophers *data, char *str)
{
	pthread_mutex_lock(&data->data->print);
	if (data->is_dead == 0)
		printf("%llu %d %s\n",
			get_time() - data->data->start, data->id + 1, str);
	pthread_mutex_unlock(&data->data->print);
}

static void	eat_meal(t_philosophers *data)
{
	pthread_mutex_lock(data->right_fork);
	print_massage(data, "has taken a fork");
	pthread_mutex_lock(data->left_fork);
	print_massage(data, "has taken a fork");
	data->data->total_eaten_meal++;
	data->eaten_meal++;
	print_massage(data, "is eating");
	data->remain_death_time = data->data->death_time;
	ft_usleep(data->data->eat_time);
	pthread_mutex_unlock(data->right_fork);
	pthread_mutex_unlock(data->left_fork);
	print_massage(data, "is sleeping");
	ft_usleep(data->data->sleep_time);
	print_massage(data, "is thinking");
}

void	*eat(void *new_data)
{
	t_philosophers	*data;

	data = (t_philosophers *)(new_data);
	if (data->id % 2 == 1)
		ft_usleep(5);
	while (data->is_dead == 0)
	{
		if (((data->data->total_eaten_meal) / data->data->number_of_philo)
			== data->eaten_meal)
		{
			eat_meal(data);
		}
	}
	return (NULL);
}
