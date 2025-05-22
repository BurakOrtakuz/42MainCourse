/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:46:16 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 20:58:33 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../include/cub3d.h"
#include <fcntl.h>
#include <unistd.h>

int	check_arg(int ac, char **av, t_map *m)
{
	int		fd;
	char	*tmp;

	set_default_map(m);
	if (ac != 2)
		error_massage("Invalid number of argument\n", m, -1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_massage("File read failed!\n", m, -1);
	if (check_cub(av[1]))
		error_massage("Invalid file type!", m, fd);
	if (check_value(fd, m) || check_map(fd, m))
	{
		tmp = get_next_line(fd);
		while (tmp)
		{
			free(tmp);
			tmp = get_next_line(fd);
		}
		error_massage("Setting map failed!\n", m, fd);
	}
	close (fd);
	if (set_mini_map(m))
		error_massage("set mini map failed!\n", m, -1);
	return (0);
}
