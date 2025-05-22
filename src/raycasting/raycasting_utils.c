/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:47:12 by bortakuz          #+#    #+#             */
/*   Updated: 2024/02/13 00:17:56 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include <math.h>

double	calculate_distance(double x1, double x2, double y1, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

t_ray	*biggest_ray(t_program *program, t_ray *ray, \
		t_f_coordinat *ray_v, t_f_coordinat *ray_h)
{
	double	h_lenght;
	double	v_lenght;

	h_lenght = calculate_distance \
	(ray_h->x, program->player.coordinat.x, \
	ray_h->y, program->player.coordinat.y);
	v_lenght = calculate_distance \
	(ray_v->x, program->player.coordinat.x, \
	ray_v->y, program->player.coordinat.y);
	if (h_lenght > v_lenght)
		return (ray->way = 1, ray->distance = \
			v_lenght, ray->coordinat = *ray_v, ray);
	return (ray->way = 2, ray->distance = \
		h_lenght, ray->coordinat = *ray_h, ray);
}
