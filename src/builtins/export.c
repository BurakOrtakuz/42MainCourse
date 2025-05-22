/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:32:11 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:39:00 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

char	*ft_get_env(char *s)
{
	int		front;
	int		back;
	char	*back_str;

	front = ft_strchr(s, '=') - s;
	back = ft_strlen(s + front + 1);
	if (!back)
		return (0);
	back_str = ft_substr(s, front + 1, back);
	return (back_str);
}

char	*ft_get_env_front(char *s)
{
	int		len;
	char	*front;

	len = ft_strchr(s, '=') - s;
	front = ft_substr(s, 0, len);
	return (front);
}

void	ft_set_env(char *s)
{
	char	*front;
	char	*back;

	if (!ft_strchr(s, '='))
	{
		ft_settle_env(s, 0);
		return ;
	}
	back = ft_get_env(s);
	front = ft_get_env_front(s);
	if (!back)
	{
		ft_settle_env(front, ft_strdup(""));
		return ;
	}
	ft_settle_env(front, back);
}

int	ft_env_check(char *s)
{
	int	i;

	i = 0;
	if (!ft_is_letter_underscore(s[i++]))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!ft_is_alnum_underscore(s[i++]))
			return (0);
	}
	return (1);
}

int	ft_export(t_command *command)
{
	int	i;

	i = 0;
	if (!command->arguments[1])
		ft_export_sort(command);
	else
	{
		while (command->arguments[++i])
		{
			if (ft_env_check(command->arguments[i]))
				ft_set_env(command->arguments[i]);
			else
			{
				ft_putstr_fd("minishell: export: '", 2);
				ft_putstr_fd(command->arguments[i], 2);
				ft_putendl_fd("':not a valid identifier", 2);
				return (1);
			}
		}
	}
	return (0);
}
