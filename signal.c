#include "minishell.h"

void	signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}

}

void	signal_setup(void)
{
	struct sigaction sa;

	sa.sa_handler = signal_handle;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT, &sa, NULL);

	// signal(SIGQUIT, SIG_IGN);
	int	i = 0;
	while (++i < NSIG)
	{
		if (i != SIGINT)
			signal(i, SIG_IGN);
	}
}


