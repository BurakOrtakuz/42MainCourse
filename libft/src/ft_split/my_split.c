/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:16:52 by envyilma          #+#    #+#             */
/*   Updated: 2024/01/29 13:27:35 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>

static char	**malloc_error(char **arr, size_t i)
{
	while (arr[i])
		free(arr[i++]);
	return (free(arr), NULL);
}

static int	word_count(char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s == c)
		{
			if (*(s + 1) == c)
				return (ft_putstr("Two new line!\n"), -3);
			s++;
		}
		else
		{
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	return (i);
}

static int	word_len(char const *s, char c)
{
	int	len;

	len = 0;
	if (!*s)
		return (0);
	while (*s && *s++ != c)
		len++;
	return (len);
}

char	**my_split(char *s, char c)
{
	char	**res;
	int		a;
	int		i;

	a = -1;
	i = (word_count(s, c) + 1);
	if (i <= 0)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * i);
	if (!s || !res)
		return (NULL);
	i = 0;
	while (++a < word_count(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		res[a] = ft_substr(s, i, word_len(&s[i], c));
		if (!res[a])
			return (malloc_error(res, 0));
		i += word_len(&s[i], c);
	}
	return (res[a] = NULL, res);
}
