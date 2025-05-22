/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:19:39 by envyilma          #+#    #+#             */
/*   Updated: 2024/03/02 19:12:25 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../include/game.h"
#include "../../include/cub3d.h"
#include "../../minilibx/mlx.h"

int	exit_game(t_program *program, char *massage)
{
	free_tmap(program->map);
	free_program(program);
	mlx_destroy_window(program->mlx, program->window);
	ft_putstr(massage);
	ft_putstr("\n");
	exit(0);
}
