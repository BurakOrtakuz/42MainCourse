/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:33:46 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:42:33 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>
#include "../../libft/include/libft.h"
#include <unistd.h>

void	ft_heredoc_sig(int sig)
{
	(void)sig;
	exit(1);
}

void	ft_heredoc_read(char *delimeter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc >> ");
		if (ft_strcmp(line, delimeter) == 0 || !line)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	ft_heredoc_proc(t_command *cmd, char *delimeter)
{
	int		retcode;
	int		pipes[2];
	pid_t	pid;

	pipe(pipes);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ft_heredoc_sig);
		close(pipes[0]);
		ft_heredoc_read(delimeter, pipes[1]);
		close(pipes[1]);
		exit(0);
	}
	close(pipes[1]);
	waitpid(pid, &retcode, 0);
	if (WEXITSTATUS(retcode) != 0)
	{
		close(pipes[0]);
		return (1);
	}
	if (cmd->in != 0)
		close(cmd->in);
	cmd->in = pipes[0];
	return (0);
}

int	ft_get_heredoc(t_command **commands)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i]->heredoc_delim && commands[i]->heredoc_delim[j])
		{
			if (ft_heredoc_proc(commands[i], commands[i]->heredoc_delim[j]))
				return (1);
			j++;
		}
		ft_free_arr_str(commands[i]->heredoc_delim);
		commands[i]->heredoc_delim = NULL;
		i++;
	}
	return (0);
}
