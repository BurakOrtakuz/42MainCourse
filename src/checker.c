/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:16:30 by bortakuz          #+#    #+#             */
/*   Updated: 2023/09/09 15:34:39 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	check_all_argumants_positive(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			print_error("Argumants have to bigger than zero");
		i++;
	}
}

static void	check_all_argumants_valid(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				print_error("Invalid argumant");
			j++;
		}
		i++;
	}
}

static void	check_number_of_argumant(int ac)
{
	if (ac != 5 && ac != 6)
		print_error("Invalid number of argumant!!!");
}

void	checker(int ac, char **av)
{
	check_number_of_argumant(ac);
	check_all_argumants_valid(av);
	check_all_argumants_positive(av);
}
