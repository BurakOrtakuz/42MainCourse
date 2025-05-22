/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 00:33:07 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:41:16 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

t_command	*ft_init_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(sizeof(t_command), 1);
	cmd->in = 0;
	cmd->out = 1;
	return (cmd);
}

int	ft_is_parseable_and_parse(t_token **tkn, int *s, int end, t_command *cmd)
{
	if (*s < end && tkn[*s]->type == WORD
		&& !ft_redir_word_token(cmd, tkn, *s))
		return (0);
	else if (*s < end && tkn[*s]->type == HEREDOC
		&& !ft_redir_heredoc(cmd, tkn, s))
		return (0);
	else if (*s < end && tkn[*s]->type == RED_INPUT
		&& !ft_redir_input(cmd, tkn, s))
		return (0);
	else if (*s < end && (tkn[*s]->type == RED_CREATE
			|| tkn[*s]->type == RED_APPEND))
		if (!ft_redir_output(cmd, tkn, s))
			return (0);
	return (1);
}

t_command	*ft_get_sub_command(t_token **tokens, int start, int end)
{
	t_command	*cmd;

	cmd = ft_init_command();
	while (tokens[start] && start < end)
	{
		if (!ft_is_parseable_and_parse(tokens, &start, end, cmd))
			return (ft_return_command_free(cmd));
		start++;
	}
	return (cmd);
}

t_command	**ft_get_commands(t_token **tokens, int start, int end)
{
	t_command	*cmd;
	t_command	**commands;
	int			i;

	commands = NULL;
	i = start;
	while (i < end)
	{
		while (i < end && tokens[i] && tokens[i]->type != PIPE)
			i++;
		cmd = ft_get_sub_command(tokens, start, i);
		if (!cmd)
			return (ft_error_command_arr(commands, NULL));
		ft_add_arr_command(&commands, cmd);
		if (tokens[i] && tokens[i]->type == PIPE && !tokens[++i])
			return (ft_error_command_arr(commands, tokens[i - 1]));
		start = i;
	}
	return (commands);
}
