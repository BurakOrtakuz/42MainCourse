/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:34:22 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:37:08 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"

char	*fill_array(int c, char a)
{
	int		i;
	char	*s;

	i = -1;
	s = (char *)malloc(sizeof(char) * (c + 1));
	if (!s)
		return (NULL);
	while (i++, i < c)
		s[i] = a;
	s[c] = '\0';
	return (s);
}

int	find_max(char **av)
{
	int	i;
	int	big;
	int	tmp;

	i = -1;
	big = ft_strlen(av[0]);
	while (i++, av[i])
	{
		tmp = ft_strlen(av[i]);
		if (tmp > big)
			big = tmp;
	}
	return (big + 4);
}

int	ft_strlen_double(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	get_angle(char way)
{
	if (way == 'N')
		return (0);
	else if (way == 'S')
		return (180);
	else if (way == 'E')
		return (270);
	else if (way == 'W')
		return (90);
	return (-1);
}

void	find_starting_locating(t_map *m)
{
	int	i;
	int	j;

	i = -1;
	while (i++, m->copy_map[i])
	{
		j = -1;
		while (j++, m->copy_map[i][j])
		{
			if (check_character(m->copy_map[i][j]) == 2)
			{
				m->starting_angle = get_angle(m->copy_map[i][j]);
				m->starting_player.x = i - 2;
				m->starting_player.y = j - 2;
				return ;
			}
		}
	}
	error_massage("starting character can't find!!\n", m, -1);
}
