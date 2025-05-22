/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:57:29 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/23 17:37:57 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static int	read_data(char **av, t_stack **stack, int digit_max)
{
	t_stack_node	*j;
	int				order;
	int				number;

	while (*av)
	{
		order = 0;
		number = ft_atoi(*av);
		digit_max++;
		j = (*stack)->head_a;
		while (j)
		{
			if (j->data == number)
				error(*stack);
			else if (number < j->data)
				j->order++;
			else 
				order++;
			j = j->next;
		}
		push_top(&(*stack)->head_a, number, order);
		av++;
	}
	return (digit_max);
}

int	main(int ac, char **av)
{
	t_stack			*stack;
	int				digit_max;

	digit_max = 0;
	stack = (t_stack *)malloc(sizeof(t_stack));
	if (!stack)
		return (0);
	if (ac == 2)
		av = ft_split(av[1], ' ');
	else
		av++;
	check_data(av);
	digit_max = read_data(av, &stack, digit_max);
	if (digit_max == 3)
		small_sort(stack);
	else if (digit_max < 45)
		sort_selection(stack, digit_max);
	else 
	{
		digit_max = digit_calculate(digit_max);
		push_swap(stack, digit_max);
	}
	free_stack(stack);
}
