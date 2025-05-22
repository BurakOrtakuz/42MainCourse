/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:45:46 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:22:48 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"

static int	fill_copy_map(char **s, t_map *map, int l2, int i)
{
	s[1] = fill_array(l2, ' ');
	if (!s[1])
		return (1);
	s[1][0] = '#';
	s[1][l2 - 1] = '#';
	while (map->map[i])
	{
		s[i + 2] = ft_strdup2(map->map[i], l2);
		if (!s[i + 2])
			return (1);
		i++;
	}
	s[i + 2] = fill_array(l2, ' ');
	if (!s[i + 2])
		return (1);
	s[i + 2][0] = '#';
	s[i + 2][l2 - 1] = '#';
	s[i + 3] = fill_array(l2, '#');
	if (!s[i + 3])
		return (1);
	s[i + 4] = NULL;
	map->copy_map = s;
	return (0);
}

int	set_copy_map(t_map *map)
{
	char	**s;
	int		l1;
	int		l2;
	int		i;

	l1 = ft_strlen_double(map->map);
	l2 = find_max(map->map);
	i = 0;
	s = (char **)malloc(sizeof(char *) * (l1 + 5));
	if (!s)
		return (ft_printf("set_copy_map->s malloc allocated failed\n"), 1);
	s[0] = fill_array(l2, '#');
	if (!s[0])
		return (1);
	return (fill_copy_map(s, map, l2, i));
}
