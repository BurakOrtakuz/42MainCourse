/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inside_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:48:45 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:20:04 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char
	corner_inside(char **map, int x, int y)
{
	if (map[x - 1][y] == '1' && \
		map[x][y - 1] == '1' && \
		map[x - 1][y - 1] == ' ')
		return (1);
	if (map[x + 1][y] == '1' && \
		map[x][y - 1] == '1' && \
		map[x + 1][y - 1] == ' ')
		return (1);
	if (map[x - 1][y] == '1' && \
		map[x][y + 1] == '1' && \
		map[x - 1][y + 1] == ' ')
		return (1);
	if (map[x + 1][y] == '1' && \
		map[x][y + 1] == '1' && \
		map[x + 1][y + 1] == ' ')
		return (1);
	return (0);
}

static char
	checker_inside(char **map, int x, int y)
{
	if (map[x + 1][y] == ' ' || map[x - 1][y] == ' ' || \
		map[x][y + 1] == ' ' || map[x][y - 1] == ' ')
		return (1);
	if (corner_inside(map, x, y))
		return (1);
	return (0);
}

void
	check_inside_map(char **map, int x, int y, t_map *m)
{
	if (checker_inside(map, x, y))
		error_massage("inside map is NOT correct!\n", m, -1);
	map[x][y] = ',';
	if (map[x + 1][y] == '0')
		check_inside_map(map, x + 1, y, m);
	if (map[x - 1][y] == '0')
		check_inside_map(map, x - 1, y, m);
	if (map[x][y + 1] == '0')
		check_inside_map(map, x, y + 1, m);
	if (map[x][y - 1] == '0')
		check_inside_map(map, x, y - 1, m);
}
