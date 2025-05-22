/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_animation_set.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:48:17 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/31 15:40:14 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_variables.h"

void	set_ghost_b_sprites(t_program *program)
{
	ft_lstadd_back(&program->sprites.ghost_down, program->mlx,
		"./Sprites/Ghosts/ghost_down1.xpm");
	ft_lstadd_back(&program->sprites.ghost_down, program->mlx,
		"./Sprites/Ghosts/ghost_down2.xpm");
	ft_lstadd_back(&program->sprites.ghost_left, program->mlx,
		"./Sprites/Ghosts/ghost_left1.xpm");
	ft_lstadd_back(&program->sprites.ghost_left, program->mlx,
		"./Sprites/Ghosts/ghost_left2.xpm");
	ft_lstadd_back(&program->sprites.ghost_right, program->mlx,
		"./Sprites/Ghosts/ghost_right1.xpm");
	ft_lstadd_back(&program->sprites.ghost_right, program->mlx,
		"./Sprites/Ghosts/ghost_right2.xpm");
	ft_lstadd_back(&program->sprites.ghost_up, program->mlx,
		"./Sprites/Ghosts/ghost_up1.xpm");
	ft_lstadd_back(&program->sprites.ghost_up, program->mlx,
		"./Sprites/Ghosts/ghost_up2.xpm");
}
