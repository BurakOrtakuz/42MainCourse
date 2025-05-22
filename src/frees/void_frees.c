/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_frees.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:32:59 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:40:59 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

void	ft_free_arr(void **arr, void (*f)(void *))
{
	int	i;

	i = 0;
	while (arr && arr[i])
		f(arr[i++]);
	free(arr);
}

void	ft_free_arr_command(t_command **commands)
{
	ft_free_arr((void **)commands, (void (*)(void *))ft_free_command);
}

void	ft_free_arr_str(char **arr)
{
	ft_free_arr((void **)arr, free);
}

void	ft_free_redir(t_redir *redir)
{
	if (redir)
	{
		free(redir->path);
		free(redir);
	}
}

void	ft_free_arr_pipeline(t_command **pipes)
{
	ft_free_arr((void **)pipes, (void (*)(void *))ft_free_pipeline);
}
