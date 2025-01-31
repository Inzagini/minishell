#include "minishell.h"

void	ft_pwd(t_env *env)
{
	char	buff[PATH_MAX];
	char	*path;

	path = getcwd(buff, PATH_MAX);
	printf("%s\n", path);
	env->last_exit_status = 0;
}

void	ft_cd(t_command *cmd, t_env *env)
{
	if (cmd->args[1] == NULL)
	{
		if (chdir(ft_get("HOME", env->env)) == -1)
		{
			print_err(ft_get("SHELL", env->env),
				strerror(errno), cmd->args[1]);
			env->last_exit_status = 1;
			return ;
		}
	}
	else if (cmd->args[2] != NULL)
	{
		print_err(ft_get("SHELL", env->env),
			"too many arguments", "cd");
		env->last_exit_status = 1;
		return ;
	}
	else if (chdir(cmd->args[1]) == -1)
	{
		print_err(ft_get("SHELL", env->env),
			strerror(errno), cmd->args[1]);
		env->last_exit_status = 1;
		return ;
	}
	env->last_exit_status = 0;
}
