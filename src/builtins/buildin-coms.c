/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin-coms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:31:52 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:39:03 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"
#include <unistd.h>

int	ft_env(t_command *cmd)
{
	int	i;

	i = -1;
	while (g_data->env[++i])
		if (ft_strchr(g_data->env[i], '='))
			ft_putendl_fd(g_data->env[i], cmd->out);
	return (0);
}

int	ft_pwd(t_command *cmd)
{
	char	buffer[4096];

	getcwd(buffer, 4096);
	ft_putendl_fd(buffer, cmd->out);
	return (0);
}

int	ft_exit(t_command *cmd)
{
	(void)cmd;
	g_data->exit_flag = 1;
	if (cmd->in == 0 && cmd->out == 1)
		ft_putendl_fd("exit", 2);
	if (cmd->arguments[1])
	{
		if (ft_is_num_str(cmd->arguments[1]))
			return (ft_atoi(cmd->arguments[1]));
		else
		{
			ft_putstr_fd("minishell: exit :", 2);
			ft_putstr_fd(cmd->arguments[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (255);
		}
	}
	return (0);
}

int	ft_echo(t_command *cmd)
{
	int	i;

	if (!cmd->arguments[1])
	{
		ft_putstr_fd("\n", cmd->out);
		return (0);
	}
	if (ft_strcmp("-n", cmd->arguments[1]) == 0 && !cmd->arguments[2])
		return (0);
	i = 1;
	if (ft_strcmp("-n", cmd->arguments[1]) != 0)
		i = 0;
	while (cmd->arguments[++i])
	{
		ft_putstr_fd(cmd->arguments[i], cmd->out);
		if (cmd->arguments[i + 1])
			ft_putstr_fd(" ", cmd->out);
	}
	if (cmd->arguments[1] && ft_strcmp("-n", cmd->arguments[1]) != 0)
		ft_putstr_fd("\n", cmd->out);
	return (0);
}

int	ft_unset(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->arguments[++i])
	{
		if (ft_env_check(cmd->arguments[i]))
		{
			ft_env_del(cmd->arguments[i]);
		}
		else
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(cmd->arguments[i], 2);
			ft_putendl_fd("':not a valid identifier", 2);
		}
	}
	return (0);
}
