/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:00:31 by bortakuz          #+#    #+#             */
/*   Updated: 2023/07/28 01:59:06 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

typedef struct node{
	int				data;
	int				order;
	struct node		*next;
}t_stack_node;

t_stack_node	*new_node(int data, int order);
void			push(t_stack_node **root, int data, int order);
void			push_top(t_stack_node **root, int data, int order);
int				pop(t_stack_node **root);
int				peek(t_stack_node *root);
#endif