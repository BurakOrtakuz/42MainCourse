/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:42:58 by envyilma          #+#    #+#             */
/*   Updated: 2024/03/02 15:47:39 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_s.h"

//checker
int		check_arg(int ac, char **av, t_map *m);
void	set_img(t_program *program);
//cherker -> check value
int		check_value(int fd, t_map *m);
int		put_sprite(char **str, char *tmp, int i);
int		put_rgb(char *tmp, int i, t_map *m, char rgb);
//cherker -> check map
int		check_map(int fd, t_map *map);
void	check_inside_map(char **map, int x, int y, t_map *m);
int		set_copy_map(t_map *map);
int		set_mini_map(t_map *map);
void	check_outside_map(char **map, int x, int y, t_map *m);
//error
void	error_massage(char *str, t_map *map, int fd);
void	free_tmap(t_map *map);
void	free_program(t_program *program);
void	free_double_array(char **s);
//value checker utils |1|2|
//1
void	set_default_map(t_map *map);
int		check_cub(char *str);
int		is_empty(char *s);
int		word_size_in_str(char *s);
int		find_first_ch(char *str);
//2
char	*substr_without_space(char *s1);
int		is_rgb_format(char *s);
int		check_height_map(void);
//map checker utils |1|2|
//1
int		set_map(int fd, t_map *map);
int		check_character(char c);
int		check_map_characters(char **av);
//2
char	*fill_array(int c, char a);
int		find_max(char **av);
int		ft_strlen_double(char **av);
void	find_starting_locating(t_map *m);

void	set_bonus_map(t_program *program);
//
int		start_set_mini_map(t_map *map);
int		width_mini_map(t_map *map, int *start);
int		length_mini_map(t_map *map);
int		function_1(char *str);
int		fill_mini_map(t_map *map, int start, char **str, int x);
#endif
