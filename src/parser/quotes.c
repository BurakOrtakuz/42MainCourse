/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:33:29 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:41:42 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

static void	ft_check_double_quotes(char *cmd, char **trimmed, int *i, char q)
{
	int		end;
	char	*cmd_temp;
	char	*env_val_temp;

	if (cmd[*i + 1] && cmd[*i + 1] == q)
		(*i) += 2;
	else
	{
		ft_quote_len(cmd + ++(*i), &end, q);
		cmd_temp = ft_substr(cmd, *i, end);
		env_val_temp = ft_expander(cmd_temp);
		ft_free_str_join(trimmed, env_val_temp);
		free(env_val_temp);
		*i += end + 1;
	}
}

static void	ft_check_single_quotes(char *cmd, char **trimmed, int *i, char q)
{
	int		end;
	char	*cmd_temp;

	if (cmd[*i + 1] && cmd[*i + 1] == '\'')
		(*i) += 2;
	else
	{
		ft_quote_len(cmd + ++(*i), &end, q);
		cmd_temp = ft_substr(cmd, *i, end);
		ft_free_str_join(trimmed, cmd_temp);
		free(cmd_temp);
		*i += end + 1;
	}
}

static void	ft_check_without_quotes(char *cmd, char **trimmed_cmd, int *index)
{
	int		end;
	char	*cmd_temp;
	char	*env_val_temp;

	get_len_of_word(cmd + (*index), &end);
	cmd_temp = ft_substr(cmd, *index, end);
	env_val_temp = ft_expander(cmd_temp);
	ft_free_str_join(trimmed_cmd, env_val_temp);
	free(env_val_temp);
	*index += end;
}

char	*ft_trim_quotes(char *cmd)
{
	int		index;
	char	*trimmed_cmd;

	trimmed_cmd = ft_calloc(sizeof(char), 1);
	index = 0;
	while (cmd[index])
	{
		if (cmd[index] == '"')
			ft_check_double_quotes(cmd, &trimmed_cmd, &index, '\"');
		else if (cmd[index] == '\'')
			ft_check_single_quotes(cmd, &trimmed_cmd, &index, '\'');
		else
			ft_check_without_quotes(cmd, &trimmed_cmd, &index);
	}
	free(cmd);
	return (trimmed_cmd);
}

void	ft_parse_quote(t_command *cmd)
{
	int	i;

	if (cmd->command)
		cmd->command = ft_trim_quotes(cmd->command);
	i = 0;
	while (cmd->arguments && cmd->arguments[i])
	{
		cmd->arguments[i] = ft_trim_quotes(cmd->arguments[i]);
		i++;
	}
	clean_null_arguments(cmd);
}
