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
char	*ft_get(char *name, char **env)
{
	while (*env != NULL)
	{
		if (ft_strncmp(*env, name, ft_strlen(name)) == 0
			&& (*env)[ft_strlen(name)] == '=')
			return (*env + ft_strlen(name) + 1);
		env++;
	}
	return (NULL);
}

int	exit_check(t_env *env)
{
	int	i;
	int	last_status;
	int	status;

	i = 0;
	status = 0;
	last_status = 0;
	waitpid(env->prev_pid, &status, 0);
	last_status = ft_wiexitstatus(status);
	if (ft_wiexitstatus(status) != 0)
		return (last_status);
	return (0);
}
