/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:34:37 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/31 16:36:30 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include <stdlib.h>

static char	**create_dummy_map(t_map *map)
{
	char	**new_map;
	int		i;
	int		j;
	char	*temp;

	new_map = (char **)malloc(sizeof(char *) * 
			map->map_x_lenght * map->map_y_lenght);
	i = 0;
	while (map->map[i])
	{
		j = 0;
		temp = (char *)malloc(sizeof(char) * ft_strlen2(map->map[i]));
		while (map->map[i][j])
		{
			temp[j] = map->map[i][j];
			j++;
		}
		new_map[i] = temp;
		i++;
	}
	return (new_map);
}

static void	is_player_reach_all_collectiables(
	char **map, int i, int j, int *coins)
{
	if (map[i][j] == 'C' || map[i][j] == 'E')
	{
		*coins += 1;
	}
	if (map[i][j] == 'E')
		map[i][j] = '1';
	if (map[i][j] == '1' || map[i][j] == 'E')
		return ;
	map[i][j] = '1';
	is_player_reach_all_collectiables(map, i + 1, j, coins);
	is_player_reach_all_collectiables(map, i - 1, j, coins);
	is_player_reach_all_collectiables(map, i, j + 1, coins);
	is_player_reach_all_collectiables(map, i, j - 1, coins);
}

static void	is_there_all_things(t_map *map)
{
	if (!(map->coin > 0 && map->player.x && map->exit.x))
		error_massage("Not Enough Things In The Map", map->map);
}

static void	found_things(t_map *map, int i, int j)
{
	if (map->map[i][j] == 'E')
	{
		if (map->exit.x)
			error_massage("Only 1 Exit Can be In The Map", map->map);
		map->exit.x = j;
		map->exit.y = i;
	}
	else if (map->map[i][j] == 'C')
		map->coin++;
	else if (map->map[i][j] == 'P')
	{
		if (map->player.x)
			error_massage("Only 1 Player Can be In The Map", map->map);
		map->player.x = i;
		map->player.y = j;
	}
	else if (map->map[i][j] != '1' && map->map[i][j] != '0')
		error_massage("Invalid Map Character", map->map);
}

void	calculate_things(t_map *map)
{
	int		i;
	int		j;
	int		coins;
	char	**dummy_map;

	i = 0;
	map->coin = 0;
	while (map->map[i])
	{
		j = -1;
		while (++j, map->map[i][j])
			found_things(map, i, j);
		i++;
	}
	is_there_all_things(map);
	map->map_x_lenght = j;
	map->map_y_lenght = i;
	coins = 0;
	dummy_map = create_dummy_map(map);
	is_player_reach_all_collectiables(
		dummy_map, map->player.x, map->player.y, &coins);
	free_map(dummy_map);
	if (coins != map->coin + 1)
		error_massage("Player Can Not Collect All Coins Or Can Not Reach Exit",
			map->map);
}
