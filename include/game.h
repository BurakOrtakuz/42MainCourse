/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:16:55 by envyilma          #+#    #+#             */
/*   Updated: 2024/03/02 18:40:32 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub3d_s.h"

void	init_program(t_program *program, t_map *map);
void	move(t_program *program);
int		key_down(int keycode, t_program *program);
int		key_up(int keycode, t_program *program);
t_ray	*biggest_ray(t_program *program, t_ray *ray, \
		t_f_coordinat *ray_v, t_f_coordinat *ray_h);
t_ray	raycasting(t_program *program, float ray);
void	put_square(t_img *img, int size, t_coordinat coordinat, t_rgb color);
void	put_pixel(t_img *img, t_coordinat coordinat, t_rgb color);
void	put_rectangle(t_img *img, t_coordinat start, \
		t_coordinat finish, t_rgb color);
void	put_img_rectangle(t_img *img, t_img *img2, t_ray *ray, int ray_offset);
void	all_rays(t_program *program, t_img *img_3d);
t_rgb	set_color(int r, int g, int b);
double	calculate_distance(double x1, double x2, double y1, double y2);
int		exit_game(t_program *program, char *massage);
int		exit_game_mouse(t_program *program);
int		render_next_frame(t_program *program);
void	horizontal_ray(t_program *program, t_f_coordinat *ray_h, \
		t_f_coordinat *_xy_, float ra);
void	vertical_ray(t_program *program, t_f_coordinat *ray_v, \
		t_f_coordinat *_xy_, float ra);
void	ray_loop(t_program *program, t_f_coordinat *ray_h, t_f_coordinat _xy_);

#endif
