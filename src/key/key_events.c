/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 02:44:50 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:29:50 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

int	key_up(int keycode, t_program *program)
{
	if (keycode == 13)
	{
		program->movement.up = 0;
	}
	else if (keycode == 0)
	{
		program->movement.left = 0;
	}
	else if (keycode == 1)
	{
		program->movement.down = 0;
	}
	else if (keycode == 2)
	{
		program->movement.right = 0;
	}
	return (0);
}

int	exit_game_mouse(t_program *program)
{
	exit_game(program, "You Closed The Game!!");
	return (0);
}
