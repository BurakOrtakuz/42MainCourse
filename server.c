/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:49:57 by bortakuz          #+#    #+#             */
/*   Updated: 2023/09/03 17:23:48 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	print_pid(int pd)
{
	if (pd >= 10)
		print_pid(pd / 10);
	write(1, &"0123456789"[pd % 10], 1);
}

void	ft_printf_pid(int pd)
{
	write(1, "PID : ", 6);
	print_pid(pd);
	write(1, "\n", 1);
}

void	get_signal_bite(int sig)
{
	static int	i = 0;
	static char	c = 0;

	if (sig == SIGUSR1)
		c += 1;
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		c = 0;
		i = 0;
	}
	else
		c = c << 1;
}

int	main(void)
{
	ft_printf_pid(getpid());
	signal(SIGUSR1, get_signal_bite);
	signal(SIGUSR2, get_signal_bite);
	while (1)
		pause();
	return (0);
}
