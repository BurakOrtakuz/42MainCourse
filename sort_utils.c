/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:20:00 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/24 08:24:55 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_bits(int data, int digit)
{
	if ((data & digit) == digit)
	{
		return (1);
	}
	return (0);
}

int	len(t_stack_node *head)
{
	int	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

int	is_sorted(t_stack_node *head)
{
	int				temp_order;
	t_stack_node	*temp;

	temp_order = head->order;
	temp = head;
	while (temp_order == temp->order && temp->next)
	{
		temp = temp->next;
		temp_order++;
	}
	if (temp->next || temp->order != temp_order)
		return (0);
	return (1);
}

int	is_full_sorted(t_stack *stack)
{
	t_stack_node	*a;
	t_stack_node	*b;

	a = stack->head_a;
	b = stack->head_b;
	if ((a && b) && (a->order && b->order) && (a->order < b->order))
		return (0);
	while (stack->head_b && b->next)
	{
		if (b->order < b->next->order)
			return (0);
		b = b->next;
	}
	while (stack->head_a && a->next)
	{
		if (a->order > a->next->order)
			return (0);
		a = a->next;
	}
	return (1);
}

int	r_or_rr(t_stack_node *head, int order)
{
	t_stack_node	*temp;
	int				i;
	int				j;
	int				check;

	check = 0;
	i = 0;
	j = 0;
	temp = head;
	while (temp)
	{
		if (temp->order == order)
			check = 1;
		if (!check)
			i++;
		else
			j++;
		temp = temp->next;
	}
	if (i < j)
		return (i);
	else
		return (-j);
}
