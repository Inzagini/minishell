#include "minishell.h"

static int	contain_only(char *str, char c);

void	ft_echo(t_command *cmd)
{
	int	index;
	int	n_flag;

	index = 0;
	n_flag = 0;
	while (cmd->args[++index])
	{
		if (cmd->args[index][0] != '-')
			break ;
		if (contain_only(cmd->args[index], 'n'))
			break ;
		else
			n_flag = 1;
	}
	while (cmd->args[index])
	{
		printf("%s", cmd->args[index++]);
		if (cmd->args[index])
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
}

static int	contain_only(char *str, char c)
{
	int	index;

	index = 0;
	while (str[++index])
	{
		if (str[index] != c)
			return (1);
	}
	return (0);
}

