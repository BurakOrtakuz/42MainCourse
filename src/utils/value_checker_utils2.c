/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_checker_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:19:38 by envyilma          #+#    #+#             */
/*   Updated: 2024/03/02 15:46:53 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"

char	*substr_without_space(char *s1)
{
	char		*s2;
	int			i;
	int			j;

	i = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (i + 1));
	if (!s2)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] && (s1[i] == ' ' || s1[i] == '\t'))
		i++;
	while (s1[i] && s1[i] != ' ' && s1[i] != '\t' && s1[i] != '\n')
	{
		s2[j] = s1[i];
		i++;
		j++;
	}
	s2[j] = '\0';
	return (s2);
}

int	is_rgb_format(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = find_first_ch(s);
	while (s[i])
	{
		while (ft_isdigit(s[i]))
			i++;
		if (s[i] == ',')
		{
			count++;
			i++;
			if (count > 2 || !ft_isdigit(s[i]) || !ft_isdigit(s[i - 2]))
				return (0);
		}
		else
			break ;
	}
	if (count != 2)
		return (0);
	if (s[i] == '\0' || s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		return (1);
	return (0);
}

int	check_height_map(void)
{
	static int	i = 0;

	i++;
	if (i <= 51)
		return (0);
	return (1);
}
