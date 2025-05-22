/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:11:11 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:57:12 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/game.h"
#include <math.h>
#include <stdlib.h>

float	set_angle(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	else if (c == 'S')
		return (M_PI / 2);
	else if (c == 'W')
		return (M_PI);
	else if (c == 'E')
		return (0);
	return (0);
}

void	init_program(t_program *program, t_map *map)
{
	program->map = map;
	program->movement.up = 0;
	program->movement.down = 0;
	program->movement.left = 0;
	program->movement.right = 0;
	program->player.coordinat.x = map->starting_player.y * 100 + 50;
	program->player.coordinat.y = map->starting_player.x * 100 + 50;
	program->player.angle = set_angle(map->map[map->starting_player.x] \
	[map->starting_player.y]);
	program->player.delta_x = cos(program->player.angle) * 5;
	program->player.delta_y = sin(program->player.angle) * 5;
	program->player_speed = 2;
	program->xpm_image = (t_img *)malloc(sizeof(t_img) * 4);
	if (!program->xpm_image)
		error_massage("xmp image > malloc error\n", program->map, -1);
	set_img(program);
	program->bonus_map.color1 = set_color(4, 0, 255);
	program->bonus_map.color2 = set_color(255, 8, 0);
	program->bonus_map.color3 = set_color(43, 255, 0);
}
