/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_operators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:16:14 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/24 08:31:22 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

void	ra(t_stack *stack, int print)
{
	t_stack_node	*temp;
	t_stack_node	*temp2;

	temp2 = stack->head_a;
	temp = stack->head_a;
	stack->head_a = stack->head_a->next;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = temp2;
	temp2->next = NULL;
	if (print)
		ft_putstr_fd("ra\n", 1);
}

void	rb(t_stack *stack, int print)
{
	t_stack_node	*temp;
	t_stack_node	*temp2;

	temp2 = stack->head_b;
	temp = stack->head_b;
	stack->head_b = stack->head_b->next;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = temp2;
	temp2->next = 0;
	if (print)
		ft_putstr_fd("rb\n", 1);
}

void	rr(t_stack *stack)
{
	ra(stack, 0);
	rb(stack, 0);
	ft_putstr_fd("rr\n", 1);
}
