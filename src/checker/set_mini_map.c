/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mini_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:37:34 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:23:16 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stdlib.h>

static void
	helper_func(t_map *map, int i)
{
	map->mini_map[i + 1] = fill_array(map->width + 2, '1');
	map->mini_map[i + 2] = NULL;
}

static void
	helper_func2(t_map *map, int i, int j)
{
	map->mini_map[i + 1][j + 1] = '1';
	map->mini_map[i + 1][j + 2] = '\0';
}

int	fill_mini_map(t_map *map, int start, char **str, int x)
{
	int	i;
	int	j;

	i = -1;
	while (i++, i < map->length)
	{
		j = -1;
		map->mini_map[i + 1] = (char *)malloc(sizeof(char) * (map->width + 3));
		if (!map->mini_map[i + 1])
			return (1);
		map->mini_map[i + 1][0] = '1';
		while (j++, j < map->width)
		{
			map->mini_map[i + 1][j + 1] = str[x][start + j];
			if (str[x][start + j] == ',')
				map->mini_map[i + 1][j + 1] = '0';
			if (map->starting_player.x + 2 == x && \
				map->starting_player.y + 2 == start + j)
				map->mini_map[i + 1][j + 1] = \
					map->map[map->starting_player.x][map->starting_player.y];
		}
		x++;
		helper_func2(map, i, j);
	}
	return (helper_func(map, i), 0);
}

void	update_starting_position(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (i++, map->mini_map[i])
	{
		j = -1;
		while (j++, map->mini_map[i][j])
		{
			if (check_character(map->mini_map[i][j]) == 2)
			{
				map->mini_map[i][j] = '0';
				map->starting_player.x = i;
				map->starting_player.y = j;
				return ;
			}
		}
	}
}

int	set_mini_map(t_map *map)
{
	int	status;

	status = start_set_mini_map(map);
	update_starting_position(map);
	map->length += 2;
	map->width += 2;
	return (status);
}
