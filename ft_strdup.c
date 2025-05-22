/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:47:17 by bortakuz          #+#    #+#             */
/*   Updated: 2023/02/01 22:40:41 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strdup(const char *s1)
{
	char	*data;

	data = (char *)malloc(ft_strlen(s1) + 1);
	if (!data)
		return (0);
	ft_memcpy(data, s1, ft_strlen(s1) + 1);
	return (data);
}
