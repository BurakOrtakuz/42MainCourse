/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:21:14 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/13 00:31:36 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

t_rgb	set_color(int r, int g, int b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

void	put_pixel(t_img *img, t_coordinat coordinat, t_rgb color)
{
	*((unsigned int *)((*img).addr + (coordinat.x) * \
	(*img).line_length + 4 * \
	(coordinat.y))) = (color.r << 16) + (color.g << 8) + color.b;
}

void	put_square(t_img *img, int size, t_coordinat coordinat, t_rgb color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			*((unsigned int *)((*img).addr + \
			(i + coordinat.x) * (*img).line_length + 4 * \
			(j + coordinat.y))) = (color.r << 16) + (color.g << 8) + color.b;
			j++;
		}
		i++;
	}
}

void
	put_rectangle(t_img *img, t_coordinat start, \
	t_coordinat finish, t_rgb color)
{
	int	i;
	int	j;

	i = start.y;
	j = start.x;
	while (i <= finish.y)
	{
		j = start.x;
		while (j <= finish.x)
		{
			*((unsigned int *)((*img).addr + (i) * (*img).line_length + 4 \
			* (j))) = (color.r << 16) + (color.g << 8) + color.b;
			j++;
		}
		i++;
	}
}

void	put_img_rectangle(t_img *img, t_img *img2, t_ray *ray, int ray_offset)
{
	int		i;
	int		j;
	float	a;

	i = ray->start.y;
	j = ray->start.x;
	a = ray->ty_full;
	while (i < ray->finish.y)
	{
		j = ray->start.x;
		while (j < ray->finish.x)
		{
			*((unsigned int *)((*img).addr + (i) * \
				(*img).line_length + 4 * (j))) =
			*((unsigned int *)((*img2).addr + ((int)a) * \
				(*img2).line_length + 4 * ((j - ray->start.x + \
					ray_offset) % 100)));
			j++;
			a += ray->ty_step;
		}
		i++;
	}
}
