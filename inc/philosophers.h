/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:33:21 by bortakuz          #+#    #+#             */
/*   Updated: 2023/09/17 15:47:19 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_data
{
	pthread_t		death_monitor;
	pthread_mutex_t	*forks;
	int				eat_time;
	int				sleep_time;
	int				death_time;
	int				number_of_philo;
	int				total_eaten_meal;
	int				total_meal;
	pthread_mutex_t	print;
	uint64_t		start;
}	t_data;

typedef struct s_philosophers
{
	int				id;
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				remain_death_time;
	int				eaten_meal;
	int				is_dead;
	t_data			*data;
}	t_philosophers;

void		print_error(char *massage);
void		exit_philo(t_data *data);

int			ft_atoi(const char *str);

void		checker(int ac, char **av);
void		set_all_argumants(t_philosophers *philo, char **av);

int			ft_usleep(useconds_t time);
u_int64_t	get_time(void);

void		*eat(void *new_data);
void		*monitor(void *new_data);
#endif