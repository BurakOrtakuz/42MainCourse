/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:33:54 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 00:33:55 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

void	ft_add_arr(void ***arr, void *new)
{
	void	**ret;
	int		i;
	int		k;

	ret = ft_calloc(sizeof(void *), ft_matrix_len((void **)*arr) + 2);
	i = 0;
	k = 0;
	while (*arr && (*arr)[k])
		ret[i++] = (*arr)[k++];
	ret[i] = new;
	free(*arr);
	(*arr) = ret;
}

void	ft_add_arr_int(int **arr, int len, int new)
{
	int	*new_arr;

	new_arr = ft_calloc(sizeof(int), len + 1);
	if (*arr)
		ft_memcpy(new_arr, *arr, sizeof(int) * len);
	new_arr[len] = new;
	free(*arr);
	*arr = new_arr;
}

void	ft_add_arr_token(t_token ***arr, t_token *new)
{
	ft_add_arr((void ***)arr, (void *)new);
}

void	ft_add_arr_str(char ***arr, char *new)
{
	ft_add_arr((void ***)arr, (void *)new);
}

void	ft_add_arr_command(t_command ***arr, t_command *new)
{
	ft_add_arr((void ***)arr, (void *)new);
}
