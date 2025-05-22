/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:32:08 by bortakuz          #+#    #+#             */
/*   Updated: 2023/09/03 17:24:27 by bortakuz         ###   ########.fr       */
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

void	get_signal_bit(int sig, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	c = 0;

	(void )(context);
	if (sig == SIGUSR1)
		c += 1;
	i++;
	if (i == 8)
	{
		if (c == '\0')
			kill(info->si_pid, SIGUSR1);
		else
		{
			write(1, &c, 1);
		}
		c = 0;
		i = 0;
	}
	else
		c = c << 1;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = get_signal_bit;
	sa.sa_flags = SA_SIGINFO;
	ft_printf_pid(getpid());
	if (sigaction(SIGUSR1, &sa, NULL) == -1) 
		return (-1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (-1);
	while (1)
		pause();
	return (0);
}
