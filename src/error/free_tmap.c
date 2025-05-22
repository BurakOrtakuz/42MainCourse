/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:50:54 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:28:28 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stdlib.h>

void	free_tmap(t_map *map)
{
	int	i;

	i = -1;
	while (i++, map->map && map->map[i])
		free(map->map[i]);
	if (!!map->map)
		free(map->map);
	i = -1;
	while (i++, map->copy_map && map->copy_map[i])
		free(map->copy_map[i]);
	if (!!map->copy_map)
		free (map->copy_map);
	i = -1;
	while (i++, map->mini_map && map->mini_map[i])
		free (map->mini_map[i]);
	if (!!map->mini_map)
		free(map->mini_map);
	if (!!map->sprite_address.n_sprite)
		free(map->sprite_address.n_sprite);
	if (!!map->sprite_address.s_sprite)
		free(map->sprite_address.s_sprite);
	if (!!map->sprite_address.e_sprite)
		free(map->sprite_address.e_sprite);
	if (!!map->sprite_address.w_sprite)
		free(map->sprite_address.w_sprite);
}

void	free_double_array(char **str)
{
	int	i;

	i = -1;
	while (i++, str[i])
		free(str[i]);
	if (!!str)
		free(str);
}
