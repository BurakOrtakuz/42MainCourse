/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_outside_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:41:09 by envyilma          #+#    #+#             */
/*   Updated: 2024/03/02 20:37:11 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char
	corner(char **map, int x, int y)
{
	if (map[x - 1][y] == '1' && \
		map[x][y - 1] == '1' && \
		(map[x - 1][y - 1] == '0' || \
		map[x - 1][y - 1] == ' ' || \
		check_character(map[x - 1][y - 1]) == 2))
		return (1);
	if (map[x + 1][y] == '1' && \
		map[x][y - 1] == '1' && \
		(map[x + 1][y - 1] == '0' || \
		map[x + 1][y - 1] == ' ' || \
		check_character(map[x + 1][y - 1]) == 2))
		return (1);
	if (map[x - 1][y] == '1' && \
		map[x][y + 1] == '1' && \
		(map[x - 1][y + 1] == '0' || \
		map[x - 1][y + 1] == ' ' || \
		check_character(map[x - 1][y + 1]) == 2))
		return (1);
	if (map[x + 1][y] == '1' && \
		map[x][y + 1] == '1' && \
		(map[x + 1][y + 1] == '0' || \
		map[x + 1][y + 1] == ' ' || \
		check_character(map[x + 1][y + 1]) == 2))
		return (1);
	return (0);
}

static char
	checker(char **map, int x, int y)
{
	if (map[x + 1][y] == '0' || map[x - 1][y] == '0' || \
		map[x][y + 1] == '0' || map[x][y - 1] == '0')
		return (1);
	if (check_character(map[x + 1][y]) == 2 || \
		check_character(map[x - 1][y]) == 2 || \
		check_character(map[x][y + 1]) == 2 || \
		check_character(map[x][y -1]) == 2)
		return (1);
	if (corner(map, x, y))
		return (1);
	return (0);
}

void
	check_outside_map(char **map, int x, int y, t_map *m)
{
	if (checker(map, x, y))
		error_massage("ALL WALLS ARE NOT ONE!\n", m, -1);
	map[x][y] = '.';
	if (map[x + 1][y] == ' ')
		check_outside_map(map, x + 1, y, m);
	if (map[x - 1][y] == ' ')
		check_outside_map(map, x - 1, y, m);
	if (map[x][y + 1] == ' ')
		check_outside_map(map, x, y + 1, m);
	if (map[x][y - 1] == ' ')
		check_outside_map(map, x, y - 1, m);
}
