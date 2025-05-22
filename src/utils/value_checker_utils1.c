/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_checker_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:50:03 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:37:29 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"

void	set_default_map(t_map *map)
{
	map->map = NULL;
	map->mini_map = NULL;
	map->copy_map = NULL;
	map->sprite_address.n_sprite = NULL;
	map->sprite_address.s_sprite = NULL;
	map->sprite_address.e_sprite = NULL;
	map->sprite_address.w_sprite = NULL;
}

int	check_cub(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == 'b' && str[i - 2] == 'u'
		&& str[i - 3] == 'c' && str[i - 4] == '.')
		return (0);
	return (1);
}

int	is_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

int	word_size_in_str(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == ' ' || *s == '\t' || *s == '\n')
		{
			s++;
		}
		else
		{
			while (*s && (*s != ' ' && *s != '\t'))
				s++;
			i++;
		}
	}
	return (i);
}

int	find_first_ch(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (i);
		i++;
	}
	return (-1);
}
