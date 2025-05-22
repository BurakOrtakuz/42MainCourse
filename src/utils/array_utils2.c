/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:33:57 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 00:33:57 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_add_arr_redir(t_redir ***arr, t_redir *new)
{
	ft_add_arr((void ***)arr, (void *)new);
}

void	ft_add_arr_pipeline(t_command ***arr, t_command *new)
{
	ft_add_arr((void ***)arr, (void *)new);
}
