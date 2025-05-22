/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 02:53:08 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/13 03:05:12 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include <math.h>

static void	key_w(int keycode, t_program *program)
{
	if (keycode == 13)
	{
		if ((program->map->mini_map[(int)((program->player.coordinat.y + \
			(program->player.delta_y * 3)) / 100)] \
			[(int)((program->player.coordinat.x + \
			(program->player.delta_x * 3)) / 100)] != '1' && \
			program->map->mini_map[(int)((program->player.coordinat.y + \
			(program->player.delta_y * 3)) / 100)] \
			[(int)((program->player.coordinat.x) / 100)] != '1' && \
			program->map->mini_map[(int)((program->player.coordinat.y) / 100)] \
			[(int)((program->player.coordinat.x + \
			(program->player.delta_x * 3)) / 100)] != '1'))
		{
			program->player.coordinat.x += round(program->player.delta_x * 2);
			program->player.coordinat.y += round(program->player.delta_y * 2);
		}
	}
}

static void	key_a(int keycode, t_program *program)
{
	if (keycode == 0)
	{
		if ((program->map->mini_map[(int)((program->player.coordinat.y - \
		(program->player.delta_x * 3)) / 100)] \
		[(int)((program->player.coordinat.x + \
		(program->player.delta_y * 3)) / 100)] != '1' && \
		program->map->mini_map[(int)((program->player.coordinat.y - \
		(program->player.delta_x * 3)) / 100)] \
		[(int)((program->player.coordinat.x) / 100)] != '1' && \
		program->map->mini_map[(int)((program->player.coordinat.y) / 100)] \
		[(int)((program->player.coordinat.x + \
		(program->player.delta_y * 3)) / 100)] != '1'))
		{
			program->player.coordinat.x += round(program->player.delta_y * 2);
			program->player.coordinat.y -= round(program->player.delta_x * 2);
		}
	}
}

static void	key_s(int keycode, t_program *program)
{
	if (keycode == 1)
	{
		if ((program->map->mini_map[(int)((program->player.coordinat.y - \
		(program->player.delta_y * 3)) / 100)] \
		[(int)((program->player.coordinat.x - \
		(program->player.delta_x * 3)) / 100)] != '1' && \
		program->map->mini_map[(int)((program->player.coordinat.y - \
		(program->player.delta_y * 3)) / 100)] \
		[(int)((program->player.coordinat.x) / 100)] != '1' && \
		program->map->mini_map[(int)((program->player.coordinat.y) / 100)] \
		[(int)((program->player.coordinat.x - \
		(program->player.delta_x * 3)) / 100)] != '1'))
		{
			program->player.coordinat.x -= round(program->player.delta_x * 2);
			program->player.coordinat.y -= round(program->player.delta_y * 2);
		}
	}
}

static void	key_d(int keycode, t_program *program)
{
	if (keycode == 2)
	{
		if ((program->map->mini_map[(int)((program->player.coordinat.y + \
		(program->player.delta_x * 3)) / 100)] \
		[(int)((program->player.coordinat.x - \
		(program->player.delta_y * 3)) / 100)] != '1' && \
		program->map->mini_map[(int)((program->player.coordinat.y + \
		(program->player.delta_x * 3)) / 100)] \
		[(int)((program->player.coordinat.x) / 100)] != '1' && \
		program->map->mini_map[(int)((program->player.coordinat.y) / 100)] \
		[(int)((program->player.coordinat.x - \
		(program->player.delta_y * 3)) / 100)] != '1'))
		{
			program->player.coordinat.x -= round(program->player.delta_y * 2);
			program->player.coordinat.y += round(program->player.delta_x * 2);
		}
	}
}

int	key_down(int keycode, t_program *program)
{
	if (keycode == 53)
		exit_game(program, "You Closed The Game!!");
	key_w(keycode, program);
	key_a(keycode, program);
	key_s(keycode, program);
	key_d(keycode, program);
	if (keycode == 123)
	{
		program->player.angle -= 0.1;
		if (program->player.angle < 0)
			program->player.angle += 2 * M_PI;
		program->player.delta_x = cos(program->player.angle) * 5;
		program->player.delta_y = sin(program->player.angle) * 5;
	}
	if (keycode == 124)
	{
		program->player.angle += 0.1;
		if (program->player.angle > 2 * M_PI)
			program->player.angle -= 2 * M_PI;
		program->player.delta_x = cos(program->player.angle) * 5;
		program->player.delta_y = sin(program->player.angle) * 5;
	}
	render_next_frame(program);
	return (0);
}
