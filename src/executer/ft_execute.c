/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 00:32:38 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:40:22 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/wait.h>

void	ft_execute_commands(t_command **cmds)
{
	int		i;
	pid_t	pid_last_command;

	i = 0;
	ft_connect_pipes(cmds);
	while (cmds[i] && !g_data->exit_flag)
		pid_last_command = ft_run_command(cmds[i++]);
	ft_close_pipes();
	if (pid_last_command != -1)
	{
		waitpid(pid_last_command, &(g_data->return_code), 0);
		g_data->return_code = g_data->return_code % 256;
	}
	while (wait(NULL) != -1)
		continue ;
}

void	ft_parser(t_token **token)
{
	t_command	**command;

	command = ft_parse_pipes(token, 0, ft_matrix_len((void **)token));
	if (command)
	{
		ft_run_sep_pipes(command);
		ft_free_pipeline(command);
	}
	ft_free_arr_token(token);
}

t_token	**ft_lexer(char *str)
{
	t_token	**tokens;
	t_token	*token;

	tokens = NULL;
	while (1)
	{
		token = ft_get_next_token(str);
		if (!token)
			break ;
		ft_add_arr_token(&tokens, token);
	}
	return (tokens);
}

void	ft_execute(char *input)
{
	t_token	**tokens;

	if (ft_check_quotes(input))
		return ;
	tokens = ft_lexer(input);
	if (!tokens)
		return ;
	if (ft_check_interpret(tokens))
	{
		ft_free_arr_token(tokens);
		return ;
	}
	ft_parser(tokens);
}
