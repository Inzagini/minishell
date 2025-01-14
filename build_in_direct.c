#include "minishell.h"

void	ft_pwd(t_command *cmd)
{
	char	buff[PATH_MAX];
	char	*path;

	path = getcwd(buff, PATH_MAX);
	printf("%s\n", path);
}
