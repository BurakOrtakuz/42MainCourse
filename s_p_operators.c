/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_p_operators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:55:51 by bortakuz          #+#    #+#             */
/*   Updated: 2023/07/28 01:58:16 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack *stack, int print)
{
	int	temp;
	int	temp2;
	int	order;
	int	order2;

	if (!stack->head_a || !stack->head_a->next)
		return ;
	temp = stack->head_a->data;
	temp2 = stack->head_a->next->data;
	order = stack->head_a->order;
	order2 = stack->head_a->next->order;
	pop(&stack->head_a);
	pop(&stack->head_a);
	push(&stack->head_a, temp, order);
	push(&stack->head_a, temp2, order2);
	if (print)
		ft_putstr_fd("sa\n", 1);
}

void	sb(t_stack *stack, int print)
{
	int	temp;
	int	temp2;
	int	order;
	int	order2;

	if (!stack->head_b || !stack->head_b->next)
		return ;
	temp = stack->head_b->data;
	temp2 = stack->head_b->next->data;
	order = stack->head_b->order;
	order2 = stack->head_b->next->order;
	pop(&stack->head_b);
	pop(&stack->head_b);
	push(&stack->head_b, temp, order);
	push(&stack->head_b, temp2, order2);
	if (print)
		ft_putstr_fd("sb\n", 1);
}

void	ss(t_stack *stack)
{
	sa(stack, 0);
	sb(stack, 0);
	ft_putstr_fd("ss\n", 1);
}

void	pa(t_stack *stack)
{
	if (!stack->head_b)
		return ;
	push(&stack->head_a, peek(stack->head_b), stack->head_b->order);
	pop(&stack->head_b);
	ft_putstr_fd("pa\n", 1);
}

void	pb(t_stack *stack)
{
	if (!stack->head_a)
		return ;
	push(&stack->head_b, peek(stack->head_a), stack->head_a->order);
	pop(&stack->head_a);
	ft_putstr_fd("pb\n", 1);
}
