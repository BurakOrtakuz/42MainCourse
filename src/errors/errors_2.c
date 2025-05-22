/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:32:25 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:39:58 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

void	ft_put_err_line(char *msg, char *data)
{
	ft_putstr_fd("minishell: ", 2);
	if (data)
	{
		ft_putstr_fd(data, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

void	ft_redir_error(t_token *token)
{
	if (token)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->data, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near ", 2);
		ft_putstr_fd("unexpected token `newline'\n", 2);
	}
	g_data->return_code = 258;
}

void	ft_file_error(t_command *cmd, char *path)
{
	if (is_file_exist(path))
	{
		ft_put_err_line("is a directory", cmd->command);
		g_data->return_code = 126;
	}
	else
	{
		g_data->return_code = 127;
		ft_put_err_line("No such file or directory", cmd->command);
	}
}
