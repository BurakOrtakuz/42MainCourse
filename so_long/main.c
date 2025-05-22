/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 23:50:31 by burak             #+#    #+#             */
/*   Updated: 2023/08/31 16:02:32 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_variables.h"

int	main(int ac, char **av)
{
	t_map		map;
	t_program	program;

	map.map = is_file_valid(ac, av);
	calculate_things(&map);
	program.map = &map; 
	set_key_hooks(&program);
}
