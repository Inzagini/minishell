#include "minishell.h"
#include <termios.h>

static struct	termios orig_termios;

void	disable_eof(void)
{
	struct termios	new_termios;

	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	new_termios = orig_termios;
	new_termios.c_cc[VEOF] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void	restore_terminal(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios) == -1)
		perror("tcsetattr");
}
