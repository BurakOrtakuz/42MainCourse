/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr_operators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:04:11 by bortakuz          #+#    #+#             */
/*   Updated: 2023/07/28 01:57:04 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stack *stack, int print)
{
	t_stack_node	*temp;
	t_stack_node	*temp2;

	temp = stack->head_a;
	while (temp->next->next)
	{
		temp = temp->next;
	}
	temp2 = temp->next;
	temp->next = 0;
	temp2->next = stack->head_a;
	stack->head_a = temp2;
	if (print)
		ft_putstr_fd("rra\n", 1);
}

void	rrb(t_stack *stack, int print)
{
	t_stack_node	*temp;
	t_stack_node	*temp2;

	temp = stack->head_b;
	while (temp->next->next)
	{
		temp = temp->next;
	}
	temp2 = temp->next;
	temp->next = 0;
	temp2->next = stack->head_b;
	stack->head_b = temp2;
	if (print)
		ft_putstr_fd("rrb\n", 1);
}

void	rrr(t_stack *stack)
{
	rra(stack, 0);
	rrb(stack, 0);
	ft_putstr_fd("rrr\n", 1);
}
