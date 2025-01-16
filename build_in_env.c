#include "minishell.h"

void	print_env(t_env *env);

void	ft_env(t_command *cmd, t_env *env)
{
	if (cmd->args[1] != 0)
	{
		printf("%s: env: only supported without options/arguments\n", getenv("SHELL"));
		env->last_exit_status = 1;
	}
	else
		print_env(env);
}

void	print_env(t_env *env)
{
	int	i;

	i = -1;
	while (env->env_current[++i])
		printf("%s\n", env->env_current[i]);
}


