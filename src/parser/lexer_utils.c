/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:33:16 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 14:02:23 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

int	ft_word_len(char *str, int *i)
{
	int	len;

	len = 0;
	while (!ft_is_delimitter(str[*i + len]) && str[*i + len])
	{
		if (ft_is_quote(str[*i + (len)]))
		{
			len++;
			while (str[*i + len] && !ft_is_quote(str[*i + len]))
				len++;
			if (ft_is_quote(str[*i + len]))
				len++;
		}
		else
			len++;
	}
	*i += len;
	return (len);
}

t_token	*ft_getwordtoken(char *str, int *i)
{
	char	*data;
	int		j;
	int		k;

	j = *i;
	if (!ft_is_delimitter(str[*i]))
	{
		data = ft_calloc(sizeof(char), ft_word_len(str, i) + 1);
		k = 0;
		while (j != *i)
		{
			data[k] = str[j];
			k++;
			j++;
		}
		data[k] = '\0';
		return (ft_create_token(data, WORD));
	}
	return (NULL);
}

t_token	*ft_get_next_token(char *str)
{
	static int	i;
	t_token		*token;

	token = NULL;
	while (str[i])
	{
		token = ft_redir_token(str, &i);
		if (token)
			break ;
		if (!ft_is_delimitter(str[i]))
			return (ft_getwordtoken(str, &i));
		else
			i++;
	}
	if (token)
		return (token);
	i = 0;
	return (NULL);
}
