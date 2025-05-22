/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:45:29 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:43:04 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/include/libft.h"
#include <unistd.h>

void	ft_save_fds(t_command *cmd)
{
	if (cmd->out != 1)
	{
		dup2(cmd->out, 1);
		close(cmd->out);
		cmd->out = 1;
	}
	if (cmd->in != 0)
	{
		dup2(cmd->in, 0);
		close(cmd->in);
		cmd->in = 0;
	}
}

int	ft_start_process(t_command *cmd, char *cmdpath)
{
	int		exec_return;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!ft_open_redirs(cmd))
		{
			g_data->exit_flag = 1;
			exit(-1);
		}
		ft_save_fds(cmd);
		ft_close_pipes();
		exec_return = execve(cmdpath, cmd->arguments, g_data->env);
		if (exec_return != 0)
		{
			ft_put_errno_msg((cmd->command));
			g_data->exit_flag = 1;
			exit(-1);
		}
	}
	return (pid);
}
