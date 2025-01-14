#include "minishell.h"

void	ft_echo(t_command *cmd)
{
	if (cmd->args[1][0] == '-')
	{
		if (cmd->args[1][1] == 'n')
		{
			printf("Option no new line\n");
		}
		else
			printf("not supported option\n");
	}
	else
	{
		printf("No option\n");
	}
}
