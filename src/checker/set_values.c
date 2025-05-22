/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:04:34 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:26:55 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"

int	put_sprite(char **str, char *tmp, int i)
{
	if (*str != NULL)
		return (ft_putstr("don't repeat in file content!!\n"), -1);
	if (tmp[i + 2] != ' ' && tmp[i + 2] != '\t')
		return (ft_putstr("wrong sprites!!\n"), -1);
	*str = substr_without_space(&tmp[i + 2]);
	if (!(*str))
		return (ft_putstr("put_sprite func.->str allocated is failed\n"), -1);
	return (1);
}

int	put_f_rgb(char *tmp, int i, t_map *m)
{
	char	**str;

	if (!is_rgb_format(&tmp[i + 1]))
		return (ft_putstr("F_rgb format is not correct!\n"), -1);
	str = ft_split(&tmp[i + 1], ',');
	if (!str)
		return (ft_putstr("set_values file->str allocate is failed!\n"), -1);
	m->f_rgb.r = ft_atoi(str[0]);
	m->f_rgb.g = ft_atoi(str[1]);
	m->f_rgb.b = ft_atoi(str[2]);
	free_double_array(str);
	return (1);
}

int	put_c_rgb(char *tmp, int i, t_map *m)
{
	char	**str;

	if (!is_rgb_format(&tmp[i + 1]))
		return (ft_putstr("C_rgb format is not correct!\n"), -1);
	str = ft_split(&tmp[i + 1], ',');
	if (!str)
		return (ft_putstr("set_values file->str allocate is failed!\n"), -1);
	m->c_rgb.r = ft_atoi(str[0]);
	m->c_rgb.g = ft_atoi(str[1]);
	m->c_rgb.b = ft_atoi(str[2]);
	free_double_array(str);
	return (1);
}

int	put_rgb(char *tmp, int i, t_map *m, char rgb)
{
	if (rgb == 'F')
		return (put_f_rgb(tmp, i, m));
	else if (rgb == 'C')
		return (put_c_rgb(tmp, i, m));
	ft_printf("put arg is failed |rgb:%c| ERROR!\n", rgb);
	return (-1);
}
