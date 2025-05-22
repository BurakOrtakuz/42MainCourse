/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 23:59:05 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/30 15:07:02 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_coordinat
{
	int	x;
	int	y;
}	t_coordinat;

typedef struct s_map
{
	char		**map;
	int			map_x_lenght;
	int			map_y_lenght;
	int			coin;
	t_coordinat	exit;
	t_coordinat	player;
	t_coordinat	ghosts;
}	t_map;

void	calculate_things(t_map *map);
void	is_map_borders_valid(char **map);
char	**is_file_valid(int ac, char **av);
char	**is_valid(int fd);
void	error_massage(char *str, char **map);
void	free_map(char **map);
int		ft_strlen2(const char *str);
void	ft_putstr(char *str, int fd);
void	ft_putnbr(int n);
char	**is_valid(int fd);
void	*ft_memcpy(char *dst, const char *src, int n);
char	*ft_strjoin2(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
#endif