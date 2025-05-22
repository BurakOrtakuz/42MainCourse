/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:03:14 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/28 14:59:21 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>
#include "./minilibx/mlx.h"

t_list	*ft_lstnew(void *mlx, char *path)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->content = mlx_xpm_file_to_image(mlx, path, &(int){0}, &(int){0});
	new->next = new;
	return (new);
}

void	ft_lstadd_back(t_list **lst, void *mlx, char *path)
{
	t_list	*aux_lst;
	t_list	*new;

	new = ft_lstnew(mlx, path);
	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		aux_lst = ft_lstlast(*lst);
		aux_lst->next = new;
		new->next = *lst;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	if (!lst)
		return (0);
	while (temp->next != lst)
		temp = temp->next;
	return (temp);
}
