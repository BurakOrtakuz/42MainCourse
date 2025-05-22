/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:32:16 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 00:32:16 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

int	ft_check_quotes(char *input)
{
	int		i;
	int		single_q;
	int		double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !double_q)
			single_q = !single_q;
		if (input[i] == '\"' && !single_q)
			double_q = !double_q;
		i++;
	}
	if (single_q || double_q)
	{
		g_data->return_code = 1;
		return (1);
	}
	return (0);
}

int	ft_check_interpret(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i]->data, ";") == 0
			|| ft_strcmp(tokens[i]->data, "&&") == 0
			|| ft_strcmp(tokens[i]->data, "||") == 0
			|| ft_strcmp(tokens[i]->data, "\\") == 0
			|| ft_strcmp(tokens[i]->data, "*") == 0)
		{
			g_data->return_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_delimitter(char chr)
{
	return (chr == ' '
		|| chr == '<'
		|| chr == '>'
		|| chr == '\t'
		|| chr == '\n'
		|| chr == '|');
}

int	ft_is_quote(char chr)
{
	return (chr == '"' || chr == '\'');
}
