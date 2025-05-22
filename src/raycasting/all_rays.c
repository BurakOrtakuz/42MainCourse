/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:19:58 by bortakuz          #+#    #+#             */
/*   Updated: 2024/03/02 14:25:12 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include <math.h>
#include <stdio.h>

#define LIMIT 1000

static float	set_angle(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	choice_image(t_program *program, t_ray *ray, \
	t_img *img_3d, float ray_angle)
{
	if (ray->way == 1)
	{
		if ((M_PI / 2) > ray_angle || ray_angle > (3 * M_PI / 2))
			put_img_rectangle(img_3d, &program->xpm_image[1], ray, \
				ray->coordinat.y);
		else if ((M_PI / 2) < ray_angle && ray_angle < (3 * M_PI / 2))
			put_img_rectangle(img_3d, &program->xpm_image[0], ray, \
				100 - ray->coordinat.y);
	}
	else if (ray->way == 2)
	{
		if (ray_angle < M_PI)
			put_img_rectangle(img_3d, &program->xpm_image[3], ray, \
				100 - ray->coordinat.x);
		else if (ray_angle > M_PI)
			put_img_rectangle(img_3d, &program->xpm_image[2], ray, \
				ray->coordinat.x);
	}
}

void	set_rays(t_ray *ray, int i)
{
	ray->line_h = (100 * 999) / (ray->distance);
	ray->ty_off = 0;
	ray->ty_step = 100 / ray->line_h;
	if (ray->line_h >= 999)
	{
		ray->ty_off = (ray->line_h - 999) / 2;
		ray->line_h = 999;
	}
	ray->ty_full = ray->ty_off * ray->ty_step;
	ray->line_off = 500 - (ray->line_h / 2);
	ray->start.x = i * 1;
	ray->start.y = (ray->line_off);
	ray->finish.x = i * 1 + 1;
	ray->finish.y = (ray->line_off + ray->line_h);
	ray->coordinat.x = ((int)ray->coordinat.x % 100);
	ray->coordinat.y = ((int)ray->coordinat.y % 100);
}

void	all_rays(t_program *program, t_img *img_3d)
{
	float		ray_angle;
	int			i;
	t_ray		ray;

	ray_angle = program->player.angle - 30 * (M_PI / 180);
	i = 0;
	while (i < LIMIT)
	{
		ray_angle = set_angle(ray_angle);
		ray = raycasting(program, ray_angle);
		ray.distance = ray.distance * cos(program->player.angle - ray_angle);
		set_rays(&ray, i);
		choice_image(program, &ray, img_3d, ray_angle);
		i++;
		ray_angle += (M_PI / 180) / LIMIT * 60;
	}
}
