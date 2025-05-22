/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:34:02 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 00:34:02 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"
#include <unistd.h>

void	ft_env_del(char *del)
{
	int		i;
	int		j;
	int		index_of_del;
	int		tot_len_env;
	char	**new_env;

	index_of_del = ft_env_index(del);
	if (index_of_del == -1)
		return ;
	tot_len_env = ft_matrix_len((void **)g_data->env);
	new_env = ft_calloc(sizeof(char *), tot_len_env);
	i = -1;
	j = 0;
	while (g_data->env[++i])
	{
		if (index_of_del == i)
			j++;
		new_env[i] = g_data->env[i + j];
	}
	free(g_data->env[index_of_del]);
	free(g_data->env);
	g_data->env = new_env;
}

void	update_env_path(void)
{
	int		pwdindex;
	char	*back;

	pwdindex = ft_env_index("PWD");
	if (pwdindex == -1)
		return ;
	back = ft_strdup(g_data->env[pwdindex]);
	ft_settle_env(ft_strdup("OLDPWD"), ft_get_env(back));
	ft_settle_env(ft_strdup("PWD"), getcwd(NULL, 4096));
	free(back);
}

int	ft_env_line_len(char *s)
{
	int	i;

	i = 0;
	while (ft_is_alnum_underscore(s[i]) && s[i])
		i++;
	return (i);
}

char	*ft_take_env(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] && token[i + 1] == '?')
			return (ft_strdup("$?"));
		else if (token[i] == '$' && token[i + 1]
			&& !ft_is_letter_underscore(token[i + 1]))
			return (ft_substr(token, i, 2));
		else if (token[i] == '$' && token[i + 1]
			&& ft_is_alnum_underscore(token[i + 1]))
			return (ft_substr(token, i, (ft_env_line_len(token + i + 1) + 1)));
		i++;
	}
	return (0);
}
