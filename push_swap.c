/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:52:05 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/23 15:47:14 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_b_emptyier(t_stack *stack, int digit)
{
	int	i;
	int	lenght;

	i = 0;
	lenght = len(stack->head_b);
	while (i < lenght)
	{
		if (check_bits(stack->head_b->order, digit * 2))
			pa(stack);
		else if (stack->head_b->next)
			rb(stack, 1);
		i++;
	}
}

void	push_swap(t_stack *stack, int max_digit)
{
	int				digit;
	int				i;
	int				j;
	int				lenght;

	j = 0;
	digit = 1;
	while (++j <= max_digit && !is_full_sorted(stack))
	{
		i = 0;
		lenght = len(stack->head_a);
		while (i < lenght && !is_full_sorted(stack))
		{
			if (!check_bits(stack->head_a->order, digit))
				pb(stack);
			else if (stack->head_a->next)
				ra(stack, 1);
			i++;
		}
		stack_b_emptyier(stack, digit);
		digit *= 2;
	}
	while (stack->head_b)
		pa(stack);
}

void	sort_selection(t_stack *stack, int lenght)
{
	int				i;

	i = 0;
	while (i < lenght - 1)
	{
		if (!selection_helper(stack, r_or_rr(stack->head_a, i)))
			break ;
		i++;
	}
	while (stack->head_b)
		pa(stack);
}

int	selection_helper(t_stack *stack, int i)
{
	if (i < 0)
	{
		while (i != 0)
		{
			rra(stack, 1);
			i++;
		}
		if (is_sorted(stack->head_a))
			return (0);
		pb(stack);
	}
	else
	{
		while (i != 0)
		{
			ra(stack, 1);
			i--;
		}
		if (is_sorted(stack->head_a))
			return (0);
		pb(stack);
	}
	return (1);
}

void	small_sort(t_stack *stack)
{
	if (is_sorted(stack->head_a))
		return ;
	if (stack->head_a->order == 0)
	{
		pb(stack);
		ra(stack, 1);
		pa(stack);
	}
	else if (stack->head_a->order == 1)
	{
		if (stack->head_a->next->order == 0)
			sa(stack, 1);
		if (is_sorted(stack->head_a))
			return ;
		rra(stack, 1);
	}
	else
	{
		ra(stack, 1);
		if (is_sorted(stack->head_a))
			return ;
		sa(stack, 1);
	}
}
