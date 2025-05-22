/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:29:55 by envyilma          #+#    #+#             */
/*   Updated: 2024/02/12 18:27:36 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_substr2(char *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	s_len;
	size_t	end;

	while (*s == ' ' || *s == '\t')
		s++;
	if (!s)
		return (0);
	s_len = ft_strlen(s);
	end = 0;
	if (start < s_len)
		end = s_len - start;
	if (end > len)
		end = len;
	s2 = (char *)malloc(sizeof(char) * (end + 1));
	if (!s2)
		return (0);
	ft_strlcpy2(s2, s + start, end + 1);
	return (s2);
}
/*
Start ile verilen değerdeki indexten başlayarak len
ile verilen değerdeki index'e kadar ki aralığı
oluşturduğu yeni parametreye kopyalar ve bu parametreyi döndürür.
*/
