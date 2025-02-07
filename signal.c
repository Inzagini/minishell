/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:46:09 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/07 17:32:23 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

int	g_sigint;

void	heredoc_signal_handler(int sig)
{
	char	eot;

	if (sig == SIGINT)
	{
		g_sigint = 1;
		eot = 4;
		rl_done = 1;
		ioctl(STDIN_FILENO, TIOCSTI, &eot);
	}
}

void	signal_handle(int sig)
{
	char	eot;

	if (sig == SIGINT)
	{
		g_sigint = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!rl_done)
			rl_redisplay();
		rl_done = 1;
		eot = 4;
		ioctl(STDIN_FILENO, TIOCSTI, &eot);
	}
}

void	signal_setup(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handle;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
}
