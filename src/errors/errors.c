/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 00:32:30 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:39:54 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <string.h>
#include "../../libft/include/libft.h"
#include <errno.h>

void	*ft_error_command_arr(t_command **commands, t_token *token)
{
	ft_free_arr_command(commands);
	if (token)
		ft_redir_error(token);
	return (NULL);
}

void	*ft_return_command_free(t_command *cmd)
{
	ft_free_command(cmd);
	return (NULL);
}

void	*ft_error_pipeline(t_command **command, t_token *token)
{
	ft_free_pipeline(command);
	if (token)
		ft_redir_error(token);
	return (NULL);
}

void	ft_put_error(void)
{
	char	*msg;

	msg = (char *)strerror(errno);
	ft_putstr_fd(msg, 2);
}

void	ft_put_errno_msg(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_put_error();
	ft_putendl_fd("", 2);
}
