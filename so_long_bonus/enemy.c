/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:49:50 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/31 14:43:35 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_variables.h"

void	move_ghost(t_program *program)
{
	int			y;
	static int	i = 1;
	static char	temp_ghost = '0';

	y = program->map->ghosts.y;
	program->sprites.ghost = program->sprites.ghost->next;
	if (program->map->map[program->map->ghosts.x][y + i] == 'P')
		exit_game(program, "You Lose!");
	else if (program->map->map[program->map->ghosts.x][y + i] != '1' 
		&& program->map->map[program->map->ghosts.x][y + i] != 'E')
	{
		program->map->map[program->map->ghosts.x][y] = temp_ghost;
		temp_ghost = program->map->map[program->map->ghosts.x][y + i];
		program->map->map[program->map->ghosts.x][y + i] = 'G';
		program->map->ghosts.y += i;
	}
	else
	{
		i *= -1;
		if (i == 1)
			program->sprites.ghost = program->sprites.ghost_right;
		else
			program->sprites.ghost = program->sprites.ghost_left;
	}
}
