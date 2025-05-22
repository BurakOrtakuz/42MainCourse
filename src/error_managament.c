/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managament.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:46:09 by bortakuz          #+#    #+#             */
/*   Updated: 2023/09/12 14:04:35 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <stdio.h>

void	print_error(char *massage)
{
	printf("Error\n%s\n", massage);
	exit(-1);
}

void	exit_philo(t_data *data)
{
	(void)data;
	exit(0);
}
