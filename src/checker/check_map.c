/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:55:24 by envyilma          #+#    #+#             */
/*   Updated: 2024/03/02 15:18:25 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"
#include <unistd.h>

int	check_map(int fd, t_map *map)
{
	if (set_map(fd, map))
		return (ft_putstr("set maps failed!\n"), 1);
	if (check_map_characters(map->map))
		return (ft_putstr("check_map_characters function failed!\n"), 1);
	if (set_copy_map(map))
		return (ft_putstr("set copy maps failed!\n"), 1);
	close(fd);
	check_outside_map(map->copy_map, 1, 1, map);
	find_starting_locating(map);
	check_inside_map(map->copy_map, map->starting_player.x + 2, \
		map->starting_player.y + 2, map);
	return (0);
}
