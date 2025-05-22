/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:58:24 by envyilma          #+#    #+#             */
/*   Updated: 2024/03/02 15:28:24 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"

static int	is_location(char *tmp, t_map *map)
{
	int	i;

	if (is_empty(tmp))
		return (0);
	i = find_first_ch(tmp);
	if (i == -1 || word_size_in_str(tmp) != 2)
		return (ft_putstr("*.cub file content WRONG!!\n"), -1);
	if (tmp[i] == 'N' && tmp[i + 1] == 'O')
		return (put_sprite(&map->sprite_address.n_sprite, tmp, i));
	else if (tmp[i] == 'W' && tmp[i + 1] == 'E')
		return (put_sprite(&map->sprite_address.w_sprite, tmp, i));
	else if (tmp[i] == 'S' && tmp[i + 1] == 'O')
		return (put_sprite(&map->sprite_address.s_sprite, tmp, i));
	else if (tmp[i] == 'E' && tmp[i + 1] == 'A')
		return (put_sprite(&map->sprite_address.e_sprite, tmp, i));
	else if (tmp[i] == 'F')
		return (put_rgb(tmp, i, map, 'F'));
	else if (tmp[i] == 'C')
		return (put_rgb(tmp, i, map, 'C'));
	else
		return (ft_putstr("WRONG MAP SPRİTES OR RGB!!\n"), -1);
	return (1);
}

static int	check_rgb_limit(t_map *map)
{
	if (map->f_rgb.b > 255 || map->f_rgb.b < 0 || map->f_rgb.g > 255 || \
		map->f_rgb.g < 0 || map->f_rgb.r > 255 || map->f_rgb.r < 0)
		return (ft_putstr("WHATT THE F_RGB LİMİTT !! \n"), 1);
	if (map->c_rgb.b > 255 || map->c_rgb.b < 0 || map->c_rgb.g > 255 || \
		map->c_rgb.g < 0 || map->c_rgb.r > 255 || map->c_rgb.r < 0)
		return (ft_putstr("WHATT THE C_RGB LİMİTT !! \n"), 1);
	return (0);
}

int	check_value(int fd, t_map *m)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < 6)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			return (1);
		while (tmp)
		{
			j = is_location(tmp, m);
			if (j == 1 && (i++))
				break ;
			else if (j == -1)
				return (ft_putstr("check value error!\n"), free(tmp), 1);
			else
				break ;
		}
		free (tmp);
	}
	return (check_rgb_limit(m));
}
