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
			return (NULL);
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd);
		if (!command)
			return (free (tmp), NULL);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
        free (command);
		i++;
	}
	return (NULL);
}

void	expand_commands(t_env *env, t_command *cmd_list)
{
    char    *command;

	while (cmd_list)
    {
        if (cmd_list->builtin_flag == 0)
		{
			command = get_cmd(env->cmd_paths, cmd_list->arguments[0]);
			if (command)
			{
                free (cmd_list->arguments[0]);
				cmd_list->arguments[0] = command;
			} 
		}
		cmd_list = cmd_list->next;
    }
}