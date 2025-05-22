/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:50:54 by envyilma          #+#    #+#             */
/*   Updated: 2024/03/02 19:12:08 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../minilibx/mlx.h"
#include <stdlib.h>

void	free_program(t_program *program)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!!program->xpm_image[i].img)
			mlx_destroy_image(program->mlx, program->xpm_image[i].img);
		i++;
	}
	if (!!program->xpm_image)
		free(program->xpm_image);
}
