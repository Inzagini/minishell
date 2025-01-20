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
	if (chdir(cmd->args[1]) == -1)
	{
		print_error(ft_getenv("SHELL", env->env_current), strerror(errno), cmd->args[1]);
		env->last_exit_status = 1;
		return ;
	}
	env->last_exit_status = 0;
}


