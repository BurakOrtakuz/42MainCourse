/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:21:29 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/13 00:17:21 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include <math.h>

static int	check_ray(t_program *program, t_f_coordinat *ray_h)
{
	return ((int)((ray_h->x) / 100) >= 0 && (int)((ray_h->y) / 100) >= 0 && \
		(int)((ray_h->y) / 100) < program->map->length && \
		(int)((ray_h->x) / 100) < program->map->width && \
		(program->map->mini_map[(int)((ray_h->y) / 100)] \
		[(int)((ray_h->x) / 100)] == '1' || \
		program->map->mini_map[(int)((ray_h->y) / 100)] \
		[(int)((ray_h->x + 0.000001) / 100)] == '1' || \
		program->map->mini_map[(int)((ray_h->y) / 100)] \
		[(int)((ray_h->x - 0.000001) / 100)] == '1' || \
		program->map->mini_map[(int)((ray_h->y + 0.000001) / 100)] \
		[(int)((ray_h->x) / 100)] == '1' || \
		program->map->mini_map[(int)((ray_h->y + 0.000001) / 100)] \
		[(int)((ray_h->x + 0.000001) / 100)] == '1' || \
		program->map->mini_map[(int)((ray_h->y + 0.000001) / 100)] \
		[(int)((ray_h->x - 0.000001) / 100)] == '1' || \
		program->map->mini_map[(int)((ray_h->y - 0.000001) / 100)] \
		[(int)((ray_h->x) / 100)] == '1' || \
		program->map->mini_map[(int)((ray_h->y - 0.000001) / 100)] \
		[(int)((ray_h->x + 0.000001) / 100)] == '1' || \
		program->map->mini_map[(int)((ray_h->y - 0.000001) / 100)] \
		[(int)((ray_h->x - 0.000001) / 100)] == '1'));
}

void	ray_loop(t_program *program, \
		t_f_coordinat *ray_h, t_f_coordinat distances)
{
	int	dof;

	dof = 0;
	while (dof < program->map->length + program->map->width)
	{
		if (check_ray(program, ray_h))
		{
			break ;
		}
		else
		{
			ray_h->x += distances.x;
			ray_h->y += distances.y;
			dof++;
		}
	}
}

void
	horizontal_ray(t_program *program, t_f_coordinat *ray_h, \
	t_f_coordinat *distances, float ra)
{
	float	tan_ra;

	tan_ra = -1 / tan(ra);
	if (ra < M_PI)
	{
		ray_h->y = floor(((program->player.coordinat.y) / 100) * 100 + 100);
		ray_h->x = ((program->player.coordinat.y - ray_h->y) * tan_ra) \
		+ program->player.coordinat.x;
		(distances->y) = 100;
		(distances->x) = -(distances->y) * tan_ra;
	}
	else if (ra > M_PI)
	{
		ray_h->y = floor(((program->player.coordinat.y) / 100) * 100 - 0);
		ray_h->x = (program->player.coordinat.y - ray_h->y) * tan_ra \
		+ program->player.coordinat.x;
		(distances->y) = -100;
		(distances->x) = -(distances->y) * tan_ra;
	}
}

void
	vertical_ray(t_program *program, t_f_coordinat *ray_v, \
	t_f_coordinat *distances, float ra)
{
	float	tan_ra;

	tan_ra = -tan(ra);
	if ((M_PI / 2) > ra || ra > (3 * M_PI / 2))
	{
		ray_v->x = floor(((program->player.coordinat.x) / 100) * 100 + 100);
		ray_v->y = ((program->player.coordinat.x - ray_v->x) * tan_ra \
		+ program->player.coordinat.y);
		(distances->x) = 100;
		(distances->y) = -(distances->x) * tan_ra;
	}
	else if ((M_PI / 2) < ra && ra < (3 * M_PI / 2))
	{
		ray_v->x = floor(((program->player.coordinat.x) / 100) * 100 - 0);
		ray_v->y = ((program->player.coordinat.x - ray_v->x) * tan_ra \
		+ program->player.coordinat.y);
		(distances->x) = -100;
		(distances->y) = -(distances->x) * tan_ra;
	}
}
