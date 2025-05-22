/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:23:14 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/31 17:41:20 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_variables.h"
#include "./minilibx/mlx.h"

static void	move_helper(t_program *program, t_vector *way)
{
	program->map->map[way->x][way->y] = 'P';
	program->map->map[program->map->player.x][program->map->player.y] = '0';
	program->map->player.x = way->x;
	program->map->player.y = way->y;
	program->game_variables.movement++;
}

static void	move(t_program *program, int x, int y)
{
	t_vector	way;
	char		symbol;

	way.x = program->map->player.x + x;
	way.y = program->map->player.y + y;
	symbol = program->map->map[way.x][way.y];
	if (symbol == 'C' || symbol == '0')
	{
		if (symbol == 'C')
			program->game_variables.collected_coin++;
		else
			program->map->map[way.x][way.y] = 'P';
		move_helper(program, &way);
		ft_putnbr(program->game_variables.movement);
		ft_putstr("\n", 1);
	}
	else if ((symbol == 'E' && 
			program->game_variables.collected_coin == program->map->coin))
		exit_game(program, "You Win!!! Congratulations!");
}
#include <stdio.h>
void	keyboard_pressed(t_program *program)
{
	if (program->game_variables.moving == KEY_A)
	{
		move(program, 0, -1);
		program->sprites.pacman = program->sprites.pacman_left;
	}
	else if (program->game_variables.moving == KEY_D)
	{
		move(program, 0, 1);
		program->sprites.pacman = program->sprites.pacman_right;
	}
	else if (program->game_variables.moving == KEY_W)
	{
		move(program, -1, 0);
		program->sprites.pacman = program->sprites.pacman_up;
	}
	else if (program->game_variables.moving == KEY_S)
	{
		move(program, 1, 0);
		program->sprites.pacman = program->sprites.pacman_down;
	}
}

int	render_next_frame(t_program *program)
{
	static int	fps = 0;

	if ((fps % 4000) == 0 && program->game_variables.movement != -1)
	{
		keyboard_pressed(program);
		mlx_clear_window(program->mlx, program->window);
		put_all_image(program);
		fps = 0;
	}
	fps++;
	return (0);
}
