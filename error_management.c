/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:22:47 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/23 16:05:52 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

void	error(t_stack *stack)
{
	if (stack)
		free_stack(stack);
	ft_putstr_fd("Error\n", 1);
	exit(0);
}

static void	free_node(t_stack_node *node)
{
	if (node->next != NULL)
		free_node(node->next);
	free(node);
}

void	free_stack(t_stack *stack)
{
	if (stack->head_a)
		free_node(stack->head_a);
	if (stack->head_b)
		free_node(stack->head_b);
	free(stack);
}
