#include "minishell.h"

void	ft_pwd(t_command *cmd)
{
	char	buff[PATH_MAX];
	char	*path;

	path = getcwd(buff, PATH_MAX);
	printf("%s\n", path);
}

void	ft_cd(t_command *cmd)
{
	if (chdir(cmd->args[1]) == -1)
	{
		print_error(getenv("SHELL"), strerror(errno), cmd->args[1]);
		return ;
	}
}


