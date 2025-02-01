#include "minishell.h"

static int	contain_only(char *str, char c);

void	ft_echo(t_command *cmd, t_env *env)
{
	int	index;
	int	n_flag;

	index = 0;
	n_flag = 0;
	while (cmd->args[++index])
	{
		if (cmd->args[index][0] != '-')
			break ;
		if (cmd->args[index][1] == '\0')
			break ;
		if (contain_only(cmd->args[index], 'n'))
			break ;
		else
			n_flag = 1;
	}
	while (cmd->args[index])
	{
		ft_putstr_fd(cmd->args[index++], 1);
		if (cmd->args[index])
			ft_putstr_fd(" ", 1);
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	env->last_exit_status = 0;
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
