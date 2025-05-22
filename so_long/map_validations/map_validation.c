/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 00:02:05 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/31 17:47:24 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include <fcntl.h>
#include "../utils/get_next_line/get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static int	check_ber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == 'r' && str[i - 2] == 'e' && 
		str[i - 3] == 'b' && str[i - 4] == '.')
		return (1);
	return (0);
}

char	**is_file_valid(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		error_massage("Invalid number of argumant!", NULL);
	if (!check_ber(av[1]))
		error_massage("Invalid file type!", NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		error_massage("File read failed", NULL);
	}
	return (is_valid(fd));
}

char	**is_valid(int fd)
{
	char	**map;
	char	*temp;
	char	*temp2;

	temp2 = "\0";
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		temp2 = ft_strjoin2(temp2, temp);
		free(temp);
	}
	map = ft_split(temp2, '\n');
	free(temp2);
	is_map_borders_valid(map);
	close(fd);
	return (map);
}

void	is_map_borders_valid(char **map)
{
	int	i;
	int	j;
	int	lenght;

	i = 0;
	j = 0;
	lenght = ft_strlen2(map[0]);
	while (map[i])
	{
		if (lenght != ft_strlen2(map[i]))
			error_massage("Invalid Map Lenght", map);
		if (map[i][0] != '1' || map[i][lenght - 1] != '1')
			error_massage("Invalid Map Border", map);
		i++;
	}
	while (j < lenght) 
	{
		if (map[0][j] != '1' || map[i - 1][j] != '1')
			error_massage("Invalid Map Border", map);
		j++;
	}
}
