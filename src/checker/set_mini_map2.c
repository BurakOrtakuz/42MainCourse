/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mini_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:37:34 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:23:54 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stdlib.h>

int	function_1(char *str)
{
	int	i;

	i = -1;
	while (i++, str[i])
	{
		if (str[i] == ',')
		{
			return (1);
		}
	}
	return (0);
}

int	length_mini_map(t_map *map)
{
	int	i;
	int	result;

	i = -1;
	result = 0;
	while (i++, map->copy_map[i])
	{
		if (function_1(map->copy_map[i]))
			result++;
	}
	return (result);
}

int	width_mini_map(t_map *map, int *start)
{
	int	i;
	int	j;
	int	result;

	i = -1;
	result = 0;
	while (i++, map->copy_map[0][i])
	{
		j = -1;
		while (j++, (map->copy_map[j] && map->copy_map[j][i]))
		{
			if (map->copy_map[j][i] == ',')
			{
				if (*start == -1)
					*start = i;
				result++;
				break ;
			}
		}
	}
	return (result);
}

int	start_set_mini_map(t_map *map)
{
	int		start;
	char	**str;
	int		i;

	start = -1;
	i = 0;
	str = map->copy_map;
	while (str[i] && !function_1(str[i]))
		i++;
	map->length = length_mini_map(map);
	map->width = width_mini_map(map, &start);
	map->mini_map = (char **)malloc(sizeof(char *) * (map->length + 3));
	if (!map->mini_map)
		return (1);
	map->mini_map[0] = fill_array(map->width + 2, '1');
	if (!map->mini_map[0])
		return (1);
	start = fill_mini_map(map, start, str, i);
	return (start);
}
