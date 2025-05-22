/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:23:45 by bortakuz          #+#    #+#             */
/*   Updated: 2023/05/10 11:01:51 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	found_conversitions(const char *string,	size_t len)
{
	size_t	i;

	i = 1;
	while (string[len + i] != '\0')
	{
		if (check_conversitions(string, len + i) == 1)
		{
			return (i + 1);
		}
		else
			i++;
	}
	return (0);
}

size_t	check_conversitions(const char	*string, size_t len)
{
	char	list_of_conversition[9];
	size_t	i;

	list_of_conversition[0] = 'c';
	list_of_conversition[1] = 's';
	list_of_conversition[2] = 'p';
	list_of_conversition[3] = 'd';
	list_of_conversition[4] = 'i';
	list_of_conversition[5] = 'u';
	list_of_conversition[6] = 'x';
	list_of_conversition[7] = 'X';
	list_of_conversition[8] = '%';
	i = 0;
	while (i < 9)
	{
		if (string[len] == list_of_conversition[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

size_t	put_variable(va_list	variables, char ar_type)
{
	if (ar_type == 'c')
		return (ft_putchar(va_arg(variables, int)));
	else if (ar_type == 's')
		return (ft_putstr(va_arg(variables, char *)));
	else if (ar_type == 'p')
		return (ft_point(va_arg(variables, unsigned long), 1));
	else if (ar_type == 'd')
		return (ft_putnbr(va_arg(variables, unsigned int)));
	else if (ar_type == 'i')
		return (ft_putnbr(va_arg(variables, int)));
	else if (ar_type == 'u')
		return (ft_unsigned(va_arg(variables, unsigned int)));
	else if (ar_type == 'x')
		return (ft_hexadecimal(va_arg(variables, unsigned int), 'x'));
	else if (ar_type == 'X')
		return (ft_hexadecimal(va_arg(variables, unsigned int), 'X'));
	else if (ar_type == '%')
		return (ft_putstr("%"));
	else
		return (0);
}

size_t	changer(const char *string, int i, va_list list)
{
	char	*flag;
	size_t	j;
	size_t	lenght;

	lenght = 0;
	j = 0;
	flag = ft_substr(string, i, found_conversitions(string, i));
	while (flag[j + 1] != '\0')
		j++;
	lenght += put_variable(list, flag[j]);
	free(flag);
	return (lenght);
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	size_t	i;
	size_t	lenght;

	lenght = 0;
	i = 0;
	va_start(args, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			lenght += changer(string, i, args);
			i++;
		}
		else
		{
			ft_putchar(string[i]);
			lenght++;
		}
		i++;
	}
	va_end(args);
	return (lenght);
}
