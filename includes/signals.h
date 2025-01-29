#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

extern volatile sig_atomic_t g_heredoc_interrupted;

void	signal_setup(void);
void	heredoc_signal_handler(int sig);

#endif
