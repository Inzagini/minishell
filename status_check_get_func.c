#include "minishell.h"

int	ft_wifexisted(int status)
{
	return ((status & 0xFF) == 0);
}

int	ft_wiexitstatus(int status)
{
	if ((status & 0xFF) == 0)
		return ((status >> 8) & 0xFF);
	return (-1);
}

// Custom getenv function
char	*ft_getenv(char *name, char **env)
{
	while (*env != NULL)
	{
		if (ft_strncmp(*env, name, ft_strlen(name)) == 0
			&& (*env)[ft_strlen(name)] == '=')
			return (*env + ft_strlen(name) + 6);
		env++;
	}
	return (NULL);
}

// char	*my_getpath(char *cmd)
// {
// 	int		i;
// 	char	*path;
// 	char	*cmd_path;
// 	char	**arr_path;

// 	if (cmd[0] == '/')
// 		if (!access(cmd, F_OK) && !access(cmd, X_OK))
// 			return (cmd);
// 	path = my_getenv("PATH");
// 	arr_path = ft_split(path, ':');
// 	if (!arr_path || !*arr_path)
// 		return (NULL);
// 	i = -1;
// 	while (arr_path[++i])
// 	{
// 		path = ft_strjoin((const char *) arr_path[i], (const char *) "/");
// 		cmd_path = ft_strjoin(path, cmd);
// 		free(path);
// 		if (!access(cmd_path, F_OK) && !access(cmd_path, X_OK))
// 			return (clean_arr(arr_path), cmd_path);
// 		free(cmd_path);
// 	}
// 	clean_arr(arr_path);
// 	return (NULL);
// }

int	exit_check(int n_cmd)
{
	int	i;
	int	last_status;
	int	status;

	i = 0;
	status = 0;
	last_status = 0;
	while (i < n_cmd)
	{
		wait(&status);
		if (ft_wiexitstatus(status) != 0)
		{
			if (ft_wiexitstatus(status) > 0)
				last_status = ft_wiexitstatus(status);
		}
		i++;
	}
	if (ft_wiexitstatus(status) == -1 || ft_wiexitstatus(status) == 1)
		return(last_status);
	return(0);
}
