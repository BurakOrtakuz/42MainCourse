/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:20:49 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:33:25 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

void	move(t_program *program)
{
	program->player.coordinat.x += program->movement.right;
	program->player.coordinat.x -= program->movement.left;
	if (program->player.coordinat.x < 0)
		program->player.coordinat.x = 0;
	if (program->player.coordinat.x > program->map->width * 100 -1)
		program->player.coordinat.x = program->map->width * 100 -1;
	program->player.coordinat.y += program->movement.down;
	program->player.coordinat.y -= program->movement.up;
	if (program->player.coordinat.y < 0)
		program->player.coordinat.y = 0;
	if (program->player.coordinat.y > program->map->length * 100 -1)
		program->player.coordinat.y = program->map->length * 100 -1;
}
