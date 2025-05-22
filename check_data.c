/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:57:17 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/23 17:40:15 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_number(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (!(s[i][j] >= '0' && s[i][j] <= '9'))
				if (!(j == 0 && (s[i][j] == '-' || s[i][j] == '+')
					&& (s[i][j + 1] >= '0' && s[i][j + 1] <= '9')))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	is_int(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (s[0] == '-' || s[0] == '+')
		len--;
	if (len < 10)
		return (1);
	if (len > 10)
		return (0);
	if (s[0] == '-')
		if (ft_strcmp("-2147483648", s) < 0)
			return (0);
	if (s[0] == '+')
		if (ft_strcmp("+2147483647", s) < 0)
			return (0);
	if (len == 10)
		if (ft_strcmp("2147483647", s) < 0)
			return (0);
	return (1);
}

static int	check_int(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_int(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	check_data(char **s)
{
	if (check_number(s) && check_int(s))
		return ;
	error(0);
}
