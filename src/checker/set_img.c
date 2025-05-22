/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:05:14 by bortakuz          #+#    #+#             */
/*   Updated: 2024/02/12 20:22:30 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../include/game.h"

void	set_img(t_program *program)
{
	program->xpm_image[0].img = mlx_xpm_file_to_image(program->mlx, \
		program->map->sprite_address.e_sprite, &(int){0}, &(int){0});
	program->xpm_image[1].img = mlx_xpm_file_to_image(program->mlx, \
		program->map->sprite_address.w_sprite, &(int){0}, &(int){0});
	program->xpm_image[2].img = mlx_xpm_file_to_image(program->mlx, \
		program->map->sprite_address.s_sprite, &(int){0}, &(int){0});
	program->xpm_image[3].img = mlx_xpm_file_to_image(program->mlx, \
		program->map->sprite_address.n_sprite, &(int){0}, &(int){0});
	if (!program->xpm_image[0].img || !program->xpm_image[1].img || \
		!program->xpm_image[2].img || !program->xpm_image[3].img)
		exit_game(program, "xpm_image is not set.");
	program->xpm_image[0].addr = mlx_get_data_addr(program->xpm_image[0].img, \
		&program->xpm_image[0].bits_per_pixel, \
		&program->xpm_image[0].line_length, &program->xpm_image[0].endian);
	program->xpm_image[1].addr = mlx_get_data_addr(program->xpm_image[1].img, \
		&program->xpm_image[1].bits_per_pixel, \
		&program->xpm_image[1].line_length, &program->xpm_image[1].endian);
	program->xpm_image[2].addr = mlx_get_data_addr(program->xpm_image[2].img, \
		&program->xpm_image[2].bits_per_pixel, \
		&program->xpm_image[2].line_length, &program->xpm_image[2].endian);
	program->xpm_image[3].addr = mlx_get_data_addr(program->xpm_image[3].img, \
		&program->xpm_image[3].bits_per_pixel, \
		&program->xpm_image[3].line_length, &program->xpm_image[3].endian);
}
