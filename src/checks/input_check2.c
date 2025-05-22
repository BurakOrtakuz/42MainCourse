/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:32:20 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 00:32:21 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

int	ft_is_letter_underscore(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_is_alnum_underscore(char c)
{
	if (ft_is_letter_underscore(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_builtin_check(char *command)
{
	if (ft_strcmp(BT_ECHO, command) == 0
		|| ft_strcmp(BT_CD, command) == 0
		|| ft_strcmp(BT_PWD, command) == 0
		|| ft_strcmp(BT_EXIT, command) == 0
		|| ft_strcmp(BT_EXPORT, command) == 0
		|| ft_strcmp(BT_UNSET, command) == 0
		|| ft_strcmp(BT_ENV, command) == 0)
		return (1);
	return (0);
}

int	ft_is_num_str(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

int	ft_path_check(char *file)
{
	if (ft_strncmp("./", file, 2) == 0
		|| ft_strncmp("/", file, 1) == 0
		|| ft_strncmp("../", file, 3) == 0)
		return (1);
	return (0);
}
