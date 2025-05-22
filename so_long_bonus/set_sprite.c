/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:29:07 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/31 17:52:51 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_variables.h"
#include "./minilibx/mlx.h"
#include <stdio.h>

static void	*ft_new_sprite(void *mlx, char *path)
{
	return (mlx_xpm_file_to_image(mlx, path, &(int){0}, &(int){0}));
}

void	set_all_sprites(t_program *program)
{
	program->sprites.pacman_down = NULL;
	program->sprites.pacman_left = NULL;
	program->sprites.pacman_right = NULL;
	program->sprites.pacman_up = NULL;
	program->sprites.ghost_down = NULL;
	program->sprites.ghost_left = NULL;
	program->sprites.ghost_right = NULL;
	program->sprites.ghost_up = NULL;
	program->game_variables.movement = 0;
	program->game_variables.moving = -1;
	program->game_variables.last_move = -1;
	set_animation_sprites(program);
	set_ghost_b_sprites(program);
	set_fonts(program);
	program->sprites.ghost = program->sprites.ghost_right;
	program->sprites.pacman = program->sprites.pacman_right;
	program->sprites.wall = ft_new_sprite(program->mlx,
			"./Sprites/Other/Walls/wall.xpm");
	program->sprites.space = ft_new_sprite(program->mlx,
			"./Sprites/Other/Walls/black.xpm");
	program->sprites.coin = ft_new_sprite(program->mlx,
			"./Sprites/Other/pacdot_food.xpm");
	program->sprites.exit = ft_new_sprite(program->mlx,
			"./Sprites/Other/portal.xpm");
}

void	check_map(char point, int i, int j, t_program *program)
{
	if (point == '1')
		mlx_put_image_to_window(program->mlx, program->window,
			program->sprites.wall, j * 32, i * 32);
	else if (point == '0')
		mlx_put_image_to_window(program->mlx, program->window,
			program->sprites.space, j * 32, i * 32);
	else if (point == 'P')
		mlx_put_image_to_window(program->mlx, program->window,
			program->sprites.pacman->content, j * 32, i * 32);
	else if (point == 'C')
	{
		mlx_put_image_to_window(program->mlx, program->window,
			program->sprites.coin, j * 32, i * 32);
	}
	else if (point == 'E')
	{
		mlx_put_image_to_window(program->mlx, program->window,
			program->sprites.exit, j * 32, i * 32);
	}
	else if (point == 'G')
		mlx_put_image_to_window(program->mlx, program->window,
			program->sprites.ghost->content, j * 32, i * 32);
}

void	put_movement(t_program *program, int y_size)
{
	int	temp;
	int	i;
	int	j;

	i = 1;
	temp = program->game_variables.movement;
	while (temp > 9)
	{
		i *= 10;
		temp /= 10;
	}
	temp = program->game_variables.movement;
	j = 0;
	while (i != 0)
	{
		mlx_put_image_to_window(program->mlx, program->window, 
			program->sprites.fonts[temp / i], j * 72, y_size * 32);
		temp %= i;
		i /= 10;
		j++;
	}
}

void	put_all_image(t_program *program)
{
	int	i;
	int	j;

	i = -1;
	while (++i, i < program->map->map_y_lenght)
	{
		j = -1;
		while (++j, j < program->map->map_x_lenght)
		{
			check_map(program->map->map[i][j], i, j, program);
		}
	}
	put_movement(program, program->map->map_y_lenght);
}
