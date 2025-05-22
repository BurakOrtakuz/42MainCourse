/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:42:21 by envyilma          #+#    #+#             */
/*   Updated: 2024/03/02 20:23:49 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../minilibx/mlx.h"
#include "../../include/game.h"
#include <stdlib.h>

void	init_program_map(t_program *program, t_map *map)
{
	program->map = map;
}

void	mlx_return_control2(t_program *program)
{
	if (!program->img1.addr)
		free(program->img1.addr);
	if (!program->img2.addr)
		free(program->img2.addr);
	if (program->img1.img)
		mlx_destroy_image(program->mlx, program->img1.img);
	if (program->img2.img)
		mlx_destroy_image(program->mlx, program->img2.img);
	mlx_destroy_window(program->mlx, program->window);
	error_massage("mlx_new_window return null!\n", program->map, -1);
}

void	mlx_return_control(t_program *program, int i, t_map *map)
{
	if (i == 1)
		init_program_map(program, map);
	if (i == 1 && !program->mlx)
		error_massage("mlx_init return null!\n", program->map, -1);
	else if (i == 2 && !program->window)
		error_massage("mlx_new_window return null!\n", program->map, -1);
	else if (i == 3 && (!program->img1.img || !program->img2.img))
	{
		if (program->img1.img)
			mlx_destroy_image(program->mlx, program->img1.img);
		if (program->img2.img)
			mlx_destroy_image(program->mlx, program->img2.img);
		mlx_destroy_window(program->mlx, program->window);
		error_massage("mlx_new_window return null!\n", program->map, -1);
	}
	else if (i == 4 && (!program->img1.addr || !program->img2.addr))
		mlx_return_control2(program);
}

int	main(int ac, char **av)
{
	t_program	program;
	t_map		map;

	if (check_arg(ac, av, &map) == 1)
		return (1);
	program.mlx = mlx_init();
	mlx_return_control(&program, 1, &map);
	program.window = mlx_new_window(program.mlx, 1000, 1000, "cub3d");
	mlx_return_control(&program, 2, NULL);
	init_program(&program, &map);
	mlx_hook(program.window, 2, (1L << 0), key_down, &program);
	mlx_hook(program.window, 3, (1L << 1), key_up, &program);
	mlx_hook(program.window, 17, 0, exit_game_mouse, &program);
	program.img1.img = mlx_new_image(program.mlx, 150, 150);
	program.img2.img = mlx_new_image(program.mlx, 1000, 1000);
	mlx_return_control(&program, 3, NULL);
	program.img1.addr = mlx_get_data_addr(program.img1.img, \
	&program.img1.bits_per_pixel, &program.img1.line_length, \
	&program.img1.endian);
	program.img2.addr = mlx_get_data_addr(program.img2.img, \
	&program.img2.bits_per_pixel, &program.img2.line_length, \
	&program.img2.endian);
	mlx_return_control(&program, 4, NULL);
	render_next_frame(&program);
	mlx_loop(program.mlx);
}
