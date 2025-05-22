/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:21:29 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/13 00:17:13 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include <math.h>

static void
	raycasting_vertical(t_program *program, t_ray *ray, \
	float ra, t_f_coordinat ray_h)
{
	t_f_coordinat			ray_v;
	t_f_coordinat			distances;

	if (ra == ((3 * M_PI) / 2) || ra == M_PI / 2)
	{
		ray_v.x = program->player.coordinat.x;
		ray_v.y = program->player.coordinat.y;
	}
	else
	{
		vertical_ray(program, &ray_v, &distances, ra);
		ray_loop(program, &ray_v, distances);
	}
	biggest_ray(program, ray, &ray_v, &ray_h);
}

t_ray
	raycasting(t_program *program, float ray_angle)
{
	t_ray					ray;
	t_f_coordinat			ray_h;
	t_f_coordinat			distances;

	if (ray_angle == M_PI || ray_angle == 0)
	{
		ray_h.x = program->player.coordinat.x;
		ray_h.y = program->player.coordinat.y;
	}
	else
	{
		horizontal_ray(program, &ray_h, &distances, ray_angle);
		ray_loop(program, &ray_h, distances);
	}
	raycasting_vertical(program, &ray, ray_angle, ray_h);
	return (ray);
}
