/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:30:49 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:42:49 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>
#include "../../libft/include/libft.h"
#include <unistd.h>

static int	get_flags(t_redir *redir)
{
	int	flags;

	if (redir->appendmode)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	return (flags);
}

static int	redirect_out(t_command *cmd, t_redir *redir)
{
	if (cmd->out != 1)
		close(cmd->out);
	cmd->out = open(redir->path, get_flags(redir), 0666);
	if (cmd->out == -1)
	{
		ft_put_errno_msg((redir->path));
		return (0);
	}
	return (1);
}

static int	redirect_in(t_command *cmd, t_redir *redir)
{
	if (cmd->in != 0)
		close(cmd->in);
	cmd->in = open(redir->path, O_RDONLY);
	if (cmd->in == -1)
	{
		ft_put_errno_msg((redir->path));
		return (0);
	}
	return (1);
}

int	ft_open_redirs(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->redirections && cmd->redirections[i])
	{
		if (cmd->redirections[i]->type == OUT_FILE)
		{
			if (!redirect_out(cmd, cmd->redirections[i]))
				return (0);
		}
		else if (cmd->redirections[i]->type == IN_FILE)
			if (!redirect_in(cmd, cmd->redirections[i]))
				return (0);
		i++;
	}
	return (1);
}

int	ft_execute_redir(t_command *cmd)
{
	if (ft_open_redirs(cmd))
	{
		g_data->return_code = 0;
		return (0);
	}
	g_data->return_code = 1;
	return (1);
}
