/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:32:02 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:39:01 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

char	*ft_add_quotes(char *s)
{
	char	*buff;
	char	*buff2;

	if (!s)
		s = ft_strdup("");
	buff = ft_strjoin("\"", s, ft_strlen(s) + 1);
	free(s);
	buff2 = ft_strjoin(buff, "\"", ft_strlen(buff) + 1);
	free(buff);
	return (buff2);
}

void	ft_bubble_sort(char **arr)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (arr[i][0] > arr[j][0])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_def_export(char **env, t_command *cmd, int i)
{
	ft_bubble_sort(env);
	while (env[++i])
	{
		ft_putstr_fd("declare -x ", cmd->out);
		ft_putendl_fd(env[i], cmd->out);
	}
	ft_free_arr_str(env);
}

void	ft_export_sort(t_command *cmd)
{
	int		i;
	char	*front;
	char	*back;
	char	**env;

	env = ft_calloc(sizeof(char *), ft_matrix_len((void **)g_data->env) + 1);
	i = -1;
	while (g_data->env[++i])
	{
		if (ft_strchr(g_data->env[i], '='))
		{
			front = ft_get_env_front(g_data->env[i]);
			back = ft_get_env(g_data->env[i]);
			back = ft_add_quotes(back);
			ft_free_str_join(&front, "=");
			ft_free_str_join(&front, back);
			free(back);
			env[i] = front;
		}
		else
			env[i] = ft_strdup(g_data->env[i]);
	}
	ft_print_def_export(env, cmd, -1);
}
