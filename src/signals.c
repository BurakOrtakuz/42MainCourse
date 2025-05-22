/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:34:36 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:43:24 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <sys/wait.h>

void	ft_signalhandler(int sig)
{
	(void)sig;
	if (g_data->sig_flag)
	{
		printf("\n");
		g_data->sig_flag = 0;
		return ;
	}
	g_data->return_code = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal(void)
{
	signal(SIGINT, ft_signalhandler);
	signal(SIGQUIT, SIG_IGN);
}
