/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_variable_changes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:41:59 by bortakuz          #+#    #+#             */
/*   Updated: 2023/05/10 08:08:44 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putstr(char *s)
{
	size_t	i;

	if (s == NULL)
	{
		return (ft_putstr("(null)"));
	}
	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

size_t	ft_putnbr(int n)
{
	char	str[13];
	int		is_neg;
	int		length;

	is_neg = (n < 0);
	ft_bzero(str, 13);
	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + ft_abs(n % 10);
		n = (n / 10);
	}
	if (is_neg)
		str[length] = '-';
	else if (length > 0)
		length--;
	while (length >= 0)
		ft_putchar(str[length--]);
	return ((size_t)(ft_strlen(str)));
}

size_t	ft_unsigned(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n >= 10)
		len += ft_unsigned(n / 10);
	write(1, &"0123456789"[n % 10], 1);
	return (len + 1);
}

size_t	ft_hexadecimal(unsigned int d, char w)
{
	size_t	len;

	len = 0;
	if (d >= 16)
		len += ft_hexadecimal(d / 16, w);
	if (w == 'X')
		write(1, &"0123456789ABCDEF"[d % 16], 1);
	if (w == 'x')
		write(1, &"0123456789abcdef"[d % 16], 1);
	return (len + 1);
}

size_t	ft_point(unsigned long w, int i)
{
	size_t	len;

	len = 0;
	if (i == 1)
	{
		len += write(1, "0x", 2);
		i = 0;
	}
	if (w >= 16)
		len += ft_point(w / 16, i);
	write(1, &"0123456789abcdef"[w % 16], 1);
	return (len + 1);
}
