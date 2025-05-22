/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:55:52 by bortakuz          #+#    #+#             */
/*   Updated: 2023/09/03 17:24:04 by bortakuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	kill_character(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (((c >> i) & 1) == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(30);
		i--;
	}
}

void	control(int sig)
{
	if (sig == SIGUSR1)
		write(1, "Massage get\n", 13);
}

int	ft_atoi(char *s)
{
	int	i;
	int	neg;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	if (!s)
		return (0);
	while ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
		i++;
	if (s[i] == '-')
		neg = -1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		num = (s[i] - '0') + (num * 10);
		i++;
	}
	return (num * neg);
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	pid = ft_atoi(av[1]);
	i = 0;
	signal(SIGUSR1, control);
	if (ac != 3)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	while (av[2][i])
	{
		kill_character(pid, av[2][i]);
		i++;
	}
	kill_character(pid, '\0');
	return (0);
}
