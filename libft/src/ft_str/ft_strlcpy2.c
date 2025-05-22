/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enveryilmaz <enveryilmaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:16:00 by envyilma          #+#    #+#             */
/*   Updated: 2024/01/23 23:23:29 by enveryilmaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ft_strlcpy2(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	if (!dst || !src)
		return (0);
	srcsize = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] != 0 && i < (dstsize - 1))
		{
			if (!(src[i] == ' ' || src[i] == '\t' || src[i] == '\n'))
				dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (srcsize);
}
/*
Verilen değer kadar karakteri src den dst'e 
kopyala garantiye almak için sonu alma ve nul koy.
kopyaladığımız arrayın uzunluğunu döndür
*/