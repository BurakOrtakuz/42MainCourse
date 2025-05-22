/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:52:22 by bortakuz          #+#    #+#             */
/*   Updated: 2023/07/30 09:32:00 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include <stdlib.h>

t_stack_node	*new_node(int data, int order)
{
	t_stack_node	*node;

	node = (t_stack_node *)malloc(sizeof(t_stack_node));
	node->data = data;
	node->next = NULL;
	node->order = order;
	return (node);
}

void	push(t_stack_node **root, int data, int order)
{
	t_stack_node	*node;

	node = new_node(data, order);
	node->next = *root;
	*root = node;
}

void	push_top(t_stack_node **root, int data, int order)
{
	t_stack_node	*temp;

	temp = *root;
	if (!temp)
	{
		*root = new_node(data, order);
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new_node(data, order);
}

int	pop(t_stack_node **root)
{
	t_stack_node	*temp;
	int				popped;

	if (!*root)
		return (-1);
	temp = *root;
	*root = (*root)->next;
	popped = temp->data;
	free(temp);
	return (popped);
}

int	peek(t_stack_node *root)
{
	if (!root)
		return (-1);
	return (root->data);
}
