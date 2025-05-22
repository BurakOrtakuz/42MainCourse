/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 00:33:25 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 00:33:25 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_run_sep_pipes(t_command **command)
{
	g_data->sig_flag = 1;
	if (ft_get_heredoc(command))
		return ;
	if (command)
		ft_execute_commands(command);
	g_data->sig_flag = 0;
}

t_command	**ft_parse_pipes(t_token **tokens, int start, int end)
{
	t_command	**command;

	if ((char)tokens[0]->data[0] == '|')
	{
		ft_redir_error(*tokens);
		return (NULL);
	}
	command = ft_get_commands(tokens, start, end);
	if (!command)
	{
		ft_free_arr_command(command);
		return (NULL);
	}
	return (command);
}
