#include "minishell.h"

volatile	sig_atomic_t g_heredoc_interrupted = 0;

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_heredoc_interrupted = 1;
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
	int					i;

	sa.sa_handler = signal_handle;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	i = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
}
