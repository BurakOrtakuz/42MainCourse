/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 00:32:07 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:39:01 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

void	only_front(char *name)
{
	if (ft_env_index(name) == -1)
		ft_add_arr_str(&(g_data->env), ft_strdup(name));
}

int	ft_set_check(char *name, char *back)
{
	if (!back)
	{
		only_front(name);
		return (0);
	}
	return (1);
}

void	ft_settle_env(char *name, char *back)
{
	char	*var;
	int		i;
	int		namelen;
	int		backlen;

	if (!ft_set_check(name, back))
		return ;
	namelen = ft_strlen(name);
	backlen = ft_strlen(back);
	var = ft_calloc(sizeof(char), namelen + backlen + 2);
	ft_memcpy(var, name, namelen);
	var[namelen] = '=';
	ft_memcpy(var + namelen + 1, back, backlen);
	i = ft_env_index(name);
	if (i != -1)
	{
		free(g_data->env[i]);
		g_data->env[i] = var;
	}
	else
		ft_add_arr_str(&(g_data->env), var);
	free(name);
	free(back);
}
