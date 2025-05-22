/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 02:32:59 by bortakuz          #+#    #+#             */
/*   Updated: 2023/02/02 16:08:29 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	size;
	size_t	alt_size;

	size = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[size] != '\0')
	{
		alt_size = 0;
		while (haystack[size + alt_size] == needle[alt_size]
			&& (size + alt_size) < len)
		{
			if (haystack[size + alt_size] == '\0' && needle[alt_size] == '\0')
				return ((char *)&haystack[size]);
			alt_size++;
		}
		if (needle[alt_size] == '\0')
			return ((char *)haystack + size);
		size++;
	}
	return (0);
}
