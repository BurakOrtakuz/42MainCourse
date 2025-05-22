/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:11:12 by envyilma          #+#    #+#             */
/*   Updated: 2024/03/02 15:46:21 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"

int	is_double_newline(char *m)
{
	int	i;

	i = 0;
	while (m && m[i] == '\n')
		i++;
	while (m && m[i] && m[i + 1])
	{
		if (m[i] == '\n' && m[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	skip_newline(char **tmp, char **m, int fd)
{
	char	*deleted;

	if (!(*m))
		return (1);
	if (!(*tmp))
		return (free(*m), 1);
	while ((**m) == '\n' && (**tmp) == '\n')
	{
		deleted = *m;
		*m = *tmp;
		*tmp = get_next_line(fd);
		free(deleted);
		if (!(*tmp))
			return (free(*m), 1);
	}
	return (0);
}

int	set_map(int fd, t_map *map)
{
	char	*tmp;
	char	*m;

	m = get_next_line(fd);
	tmp = get_next_line(fd);
	if (skip_newline(&tmp, &m, fd))
		return (1);
	while (tmp)
	{
		if (ft_strlen(tmp) > 50 || check_height_map())
			return (free(tmp), free(m), ft_printf("MAP IS TOO BIG!\n"), 1);
		m = ft_strjoin_free(m, tmp);
		if (!m)
			return (1);
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (is_double_newline(m))
		return (free(m), ft_putstr("Double new line !!\n"), 1);
	map->map = ft_split(m, '\n');
	if (!map->map)
		return (1);
	free(m);
	return (0);
}

int	check_character(char c)
{
	if (c == ' ' || c == '1' || c == '0' || c == '#')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (2);
	return (0);
}

int	check_map_characters(char **av)
{
	int	i;
	int	j;
	int	p;
	int	res;

	p = 0;
	i = -1;
	while (i++, av[i])
	{
		j = -1;
		while (j++, av[i][j])
		{
			res = check_character(av[i][j]);
			if (res == 2)
				p++;
			if (!res)
				return (ft_printf("%c UNDEFİNED CHARACTER!!\n", av[i][j]), 1);
			if (p > 1)
				return (ft_printf("Two or more starting position!!\n"), 1);
		}
	}
	if (p != 1)
		return (ft_printf("Map must have one starting position ch!!\n"), 1);
	return (0);
}
