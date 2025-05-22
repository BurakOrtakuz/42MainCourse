/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 23:57:10 by bortakuz          #+#    #+#             */
/*   Updated: 2023/08/31 15:46:04 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_strlen2(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str, int fd)
{
	write(fd, str, ft_strlen2(str));
}

void	*ft_memcpy(char *dst, const char *src, int n)
{
	int	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	while ((index + 1) < size && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	if (size)
		dst[index] = '\0';
	return (ft_strlen2(src));
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*string;
	size_t	length;

	length = ft_strlen2(s1);
	string = (char *)malloc(length + ft_strlen2(s2) + 1);
	if (string && s1 && s2)
	{
		ft_strlcpy(string, s1, length + 1);
		while (*s2)
			string[length++] = *s2++;
		string[length] = '\0';
	}
	if (s1[0] != '\0')
		free(s1);
	return (string);
}
