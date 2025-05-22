/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:34:31 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:43:18 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/include/libft.h"
#include <unistd.h>

t_data	*g_data;

char	*ft_prompt(void)
{
	char	*input;

	input = readline("minishell$ <> ");
	if (input && *input)
		add_history(input);
	return (input);
}

void	ft_init_program(char **env)
{
	g_data = ft_calloc(sizeof(t_data), 1);
	g_data->return_code = 0;
	g_data->exit_flag = 0;
	g_data->pipe_count = 0;
	g_data->sig_flag = 0;
	g_data->opened_pipes = NULL;
	g_data->env = ft_dup_matrix(env);
}

void	ft_init_proccess(void)
{
	char	*input;

	while (!g_data->exit_flag)
	{
		input = ft_prompt();
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		ft_execute(input);
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	exit_status;

	(void)argv;
	if (argc > 1)
		return (printf("minishell: too many arguments\n"));
	ft_init_program(env);
	ft_signal();
	ft_init_proccess();
	exit_status = g_data->return_code;
	ft_free_matrix((void **)g_data->env);
	free(g_data);
	return (exit_status);
}
