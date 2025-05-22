/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:45:25 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/23 09:11:23 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

void	init_bonus_map(t_bonus_map *m, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			m->map[i][j] = 'X';
			j++;
		}
		i++;
	}
}

static void
	ffunction(t_program *program, int player_y, int player_x)
{
	t_coordinat	c;
	int			i;
	int			j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			c.x = i * 30;
			c.y = j * 30;
			if (i == player_y && j == player_x)
				put_square(&program->img1, 30, \
					c, program->bonus_map.color3);
			else if (program->bonus_map.map[i][j] == '0')
				put_square(&program->img1, 30, \
				c, program->bonus_map.color1);
			else
				put_square(&program->img1, 30, \
				c, program->bonus_map.color2);
			j++;
		}
		i++;
	}
}

static void
	ffunction3(t_program *program, int i, int i2, int j)
{
	int	j2;
	int	limit_j;

	j2 = 0;
	limit_j = j + 5;
	while (j < limit_j)
	{
		if (j >= program->map->width)
			break ;
		if (program->map->mini_map[i] && program->map->mini_map[i][j] && \
			program->map->mini_map[i][j] == '0')
			program->bonus_map.map[i2][j2] = '0';
		if (program->map->mini_map[i] && program->map->mini_map[i][j] && \
			program->map->mini_map[i][j] == '1')
			program->bonus_map.map[i2][j2] = '1';
		j2++;
		j++;
	}
}

static void
	ffunction2(t_program *program, int x, int y)
{
	int	limit_i;
	int	i;
	int	i2;
	int	j;

	i = y;
	i2 = 0;
	limit_i = i + 5;
	while (i < limit_i)
	{
		if (i >= program->map->length)
			break ;
		j = x;
		ffunction3(program, i, i2, j);
		i2++;
		i++;
	}
}

void	set_bonus_map(t_program *program)
{
	int	player_x;
	int	player_y;
	int	x;
	int	y;

	player_x = 2;
	player_y = 2;
	x = program->player.coordinat.x / 100 -2;
	y = program->player.coordinat.y / 100 -2;
	if (x < 0)
	{
		x = 0;
		player_x = 1;
	}
	if (y < 0)
	{
		y = 0;
		player_y = 1;
	}
	init_bonus_map(&program->bonus_map, 5, 5);
	ffunction2(program, x, y);
	program->bonus_map.map[player_y][player_x] = 'P';
	ffunction(program, player_y, player_x);
}
