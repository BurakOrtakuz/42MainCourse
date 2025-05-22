/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:45:10 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/31 16:02:22 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_variables.h"
#include "./minilibx/mlx.h"
#include <stdlib.h>

int	exit_game(t_program *program, char *massage)
{
	free_map(program->map->map);
	free_sprite(program);
	mlx_destroy_window(program->mlx, program->window);
	ft_putstr(massage, 1);
	ft_putstr("\n", 1);
	exit(0);
}

int	exit_game_mouse(t_program *program)
{
	exit_game(program, "You Closed The Game!!");
	return (0);
}

void	set_key_hooks(t_program *program)
{
	program->mlx = mlx_init();
	program->window = mlx_new_window(program->mlx, 
			32 * program->map->map_x_lenght, 32 
			* (program->map->map_y_lenght) + 121, "so_long");
	set_all_sprites(program);
	program->game_variables.collected_coin = 0;
	mlx_hook(program->window, 2, (1L << 0), key_down, program);
	mlx_hook(program->window, 3, (1L << 1), key_up, program);
	mlx_hook(program->window, 17, 0, exit_game_mouse, program);
	mlx_loop_hook(program->mlx, render_next_frame, program);
	mlx_loop(program->mlx);
}
