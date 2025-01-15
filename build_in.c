#include "minishell.h"

int	ft_strcmp(char *s1, char *s2);

void	call_build_in(t_command *cmd, t_env *env)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		printf("unsupport\n");
	else if (!ft_strcmp(cmd->args[0], "env"))
		printf("unsupport\n");
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd, env);

}

int	ft_strcmp(char *s1, char *s2)
{
	int	index;

	index = 0;
	while (s1[index] == s2[index] && (s1[index] || s2[index]))
		index++;
	return (s1[index] - s2[index]);
}
