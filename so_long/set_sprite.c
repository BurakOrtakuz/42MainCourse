/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:29:07 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/31 17:42:16 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_variables.h"
#include "./minilibx/mlx.h"

static void	*ft_new_sprite(void *mlx, char *path)
{
	return (mlx_xpm_file_to_image(mlx, path, &(int){0}, &(int){0}));
}

void	set_all_sprites(t_program *program)
{
	program->sprites.pacman_down = ft_new_sprite(program->mlx,
			"./Sprites/Pac-Man/pac_semi_down.xpm");
	program->sprites.pacman_left = ft_new_sprite(program->mlx,
			"./Sprites/Pac-Man/pac_semi_left.xpm");
	program->sprites.pacman_right = ft_new_sprite(program->mlx,
			"./Sprites/Pac-Man/pac_semi_right.xpm");
	program->sprites.pacman_up = ft_new_sprite(program->mlx,
			"./Sprites/Pac-Man/pac_semi_up.xpm");
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
			program->sprites.pacman, j * 32, i * 32);
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
}
