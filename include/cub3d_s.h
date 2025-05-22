/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_s.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:43:00 by envyilma          #+#    #+#             */
/*   Updated: 2024/03/02 19:13:44 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_S_H
# define CUB3D_S_H

typedef struct s_coordinat
{
	int	x;
	int	y;
}		t_coordinat;

typedef struct s_f_coordinat
{
	float	x;
	float	y;
}			t_f_coordinat;

typedef struct s_ray
{
	t_f_coordinat	coordinat;
	float			distance;
	int				way;
	float			line_h;
	float			ty_off;
	float			ty_step;
	float			ty_full;
	float			line_off;
	t_coordinat		start;
	t_coordinat		finish;
}					t_ray;

typedef struct s_movement
{
	int	right;
	int	left;
	int	up;
	int	down;
}		t_movement;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_player
{
	t_coordinat	coordinat;
	float		delta_x;
	float		delta_y;
	float		angle;
}				t_player;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_sprite_address
{
	char	*n_sprite;
	char	*s_sprite;
	char	*e_sprite;
	char	*w_sprite;
}			t_sprite_address;

typedef struct s_map
{
	char				**map;
	char				**mini_map;
	char				**copy_map;
	int					length;
	int					width;
	t_coordinat			starting_player;
	float				starting_angle;
	int					max_;
	t_sprite_address	sprite_address;
	t_rgb				f_rgb;
	t_rgb				c_rgb;
}						t_map;

typedef struct s_bonus_map
{
	char	map[5][5];
	t_rgb	color1;
	t_rgb	color2;
	t_rgb	color3;
}	t_bonus_map;

typedef struct s_program
{
	void				*mlx;
	void				*window;
	t_bonus_map			bonus_map;
	t_movement			movement;
	t_player			player;
	int					player_speed;
	t_map				*map;
	t_img				*xpm_image;
	t_img				img1;
	t_img				img2;
}						t_program;
#endif
