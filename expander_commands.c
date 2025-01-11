#include "minishell.h"

char	*find_path(char **envp)
{
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			flag = 1;
		i++;
	}
	if (flag == 0)
		return (NULL);
	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	return (envp[i] + 5);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd);
		if (!command)
			return (free (tmp), NULL);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}