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
	env->last_exit_status = 0;
	if (cmd->args[1] == NULL)
	{
		if (chdir(ft_get("HOME", env->env)) == -1)
		{
			print_err(ft_get("SHELL", env->env),
				strerror(errno), cmd->args[1]);
			env->last_exit_status = 1;
		}
	}
	else if (cmd->args[2] != NULL)
	{
		print_err(ft_get("SHELL", env->env),
			"too many arguments", "cd");
		env->last_exit_status = 1;
	}
	else if (chdir(cmd->args[1]) == -1)
	{
		print_err(ft_get("SHELL", env->env),
			strerror(errno), cmd->args[1]);
		env->last_exit_status = 1;
	}
	update_pwd(env);
	return ;
}

void	update_pwd(t_env *env)
{
	char	*pwd;
	char	*old_pwd;

	pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!pwd)
	{
		print_err(ft_get("SHELL", env->env),
			"update pwd failed", NULL);
		env->last_exit_status = 1;
		return ;
	}
	old_pwd = ft_strjoin("OLDPWD=", ft_get("PWD", env->env));
	if (!old_pwd)
	{
		print_err(ft_get("SHELL", env->env),
			"update pwd failed", NULL);
		env->last_exit_status = 1;
		free (pwd);
		return ;
	}
	export_to_env(pwd, env);
	export_to_exp(pwd, env);
	export_to_env(old_pwd, env);
	export_to_exp(old_pwd, env);
}
