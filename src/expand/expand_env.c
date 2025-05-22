/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:32:46 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/27 15:40:38 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

char	*ft_expander(char *token)
{
	char	*env;
	char	*env_back;

	while (1)
	{
		env = ft_take_env(token);
		if (!env)
			break ;
		if (ft_strnstr(env, "$?", ft_strlen(env)) && ft_strlen(env) == 2)
		{
			env_back = ft_itoa(g_data->return_code);
			replace_with(&token, env, env_back);
			free(env_back);
		}
		else
		{
			env_back = get_env(env + 1);
			replace_with(&token, env, env_back);
		}
		free(env);
	}
	return (token);
}
