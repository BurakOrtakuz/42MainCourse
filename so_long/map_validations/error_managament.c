/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managament.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:02:54 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/31 16:36:56 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../mlx_variables.h"
#include "../minilibx/mlx.h"

void	free_map(char **map)
{
	int	ecx;

	ecx = -1;
	while (++ecx, map[ecx])
	{
		free(map[ecx]);
		map[ecx] = (void *)0;
	}
	free(map);
	map = (void *)0;
}

void	free_sprite(t_program *program)
{
	mlx_destroy_image(program->mlx, program->sprites.coin);
	mlx_destroy_image(program->mlx, program->sprites.exit);
	mlx_destroy_image(program->mlx, program->sprites.space);
	mlx_destroy_image(program->mlx, program->sprites.wall);
	mlx_destroy_image(program->mlx, program->sprites.pacman_down);
	mlx_destroy_image(program->mlx, program->sprites.pacman_left);
	mlx_destroy_image(program->mlx, program->sprites.pacman_right);
	mlx_destroy_image(program->mlx, program->sprites.pacman_up);
}

void	error_massage(char *str, char **map)
{
	ft_putstr("Error\n", 1);
	ft_putstr(str, 1);
	if (map)
		free_map(map);
	exit(-1);
}
