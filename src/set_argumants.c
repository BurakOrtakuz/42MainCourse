/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argumants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:28:02 by bortakuz          #+#    #+#             */
/*   Updated: 2023/09/17 15:48:10 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	set_threads(t_data *data, t_philosophers *all_philos)
{
	int	i;

	pthread_create(&data->death_monitor, NULL, monitor, (void *)(&all_philos));
	i = -1;
	while (i++, i < data->number_of_philo)
	{
		pthread_create(&all_philos->philo, NULL, eat,
			(void *)(&all_philos[i]));
	}
	pthread_join(data->death_monitor, NULL);
	i = -1;
	while (i++, i < data->number_of_philo)
	{
		pthread_join(all_philos[i].philo, NULL);
	}
}

static void	set_forks(t_data *data, t_philosophers *all_philos)
{
	int	i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->number_of_philo);
	i = -1;
	while (++i, i < data->number_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
	}
	i = -1;
	while (i++, i < data->number_of_philo)
	{
		all_philos[i].left_fork = &data->forks[(i + 1)
			% data->number_of_philo];
		all_philos[i].right_fork = &data->forks[i];
	}
}

static void	set_philos(t_data *data, t_philosophers	*all_philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		all_philos[i].id = i;
		all_philos[i].eaten_meal = 0;
		all_philos[i].remain_death_time = data->death_time;
		all_philos[i].is_dead = 0;
		all_philos[i].data = data;
		i++;
	}
}

static void	set_basic_data(t_data *data, char **av)
{
	int	temp_eat_time;
	int	temp_sleep_time;
	int	temp_total_eat;
	int	temp_death_time;

	data->number_of_philo = ft_atoi(av[1]);
	temp_death_time = ft_atoi(av[2]);
	temp_eat_time = ft_atoi(av[3]);
	temp_sleep_time = ft_atoi(av[4]);
	if (av[5])
		temp_total_eat = ft_atoi(av[5]);
	else
		temp_total_eat = -1;
	pthread_mutex_init(&data->print, NULL);
	data->total_meal = temp_total_eat;
	data->total_eaten_meal = 0;
	data->start = 0;
	data->death_time = temp_death_time;
	data->eat_time = temp_eat_time;
	data->sleep_time = temp_sleep_time;
}

void	set_all_argumants(t_philosophers *philo, char **av)
{
	t_data	data;

	set_basic_data(&data, av);
	philo = (t_philosophers *)malloc(sizeof(t_philosophers)
			* data.number_of_philo);
	set_philos(&data, philo);
	set_forks(&data, philo);
	set_threads(&data, philo);
}
