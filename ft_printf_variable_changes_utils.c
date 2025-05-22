/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_variable_changes_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:55:42 by bortakuz          #+#    #+#             */
/*   Updated: 2023/05/10 07:26:55 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	if (!b)
		return (NULL);
	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

size_t	ft_putchar(char s)
{
	write(1, &s, 1);
	return (1);
}
