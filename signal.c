/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:46:09 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:46:10 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

volatile sig_atomic_t	g_heredoc_interrupted;

void	heredoc_signal_handler(int sig)
{
	char	nl;

	if (sig == SIGINT)
	{
		g_heredoc_interrupted = 1;
		nl = '\n';
		ioctl(STDIN_FILENO, TIOCSTI, &nl);
	}
}

void	signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!rl_done)
			rl_redisplay();
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
