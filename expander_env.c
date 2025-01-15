#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->cmd_paths = NULL;
	env->env_current = NULL;
	env->export_current = NULL;
	env->full_path = NULL;
	env->last_exit_status = 0;
	env->env_current = copy_envp(envp);
	if (env->env_current == NULL)
		return (free(env), NULL);
	env->export_current = copy_envp(envp);
	if (env->export_current == NULL)
		return (clean_env(env), free(env), NULL);
	env->full_path = find_path(env->env_current);
	if (!env->full_path)
		return (clean_env(env), free(env), NULL);
	env->cmd_paths = ft_split(env->full_path, ':');
	if (!env->cmd_paths)
		return (clean_env(env), free(env), NULL);
	return (env);
}



char	**copy_envp(char **envp)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc ((i + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	copy[i] = 0;
	j = -1;
	while (envp[++j])
	{
		copy[j] = ft_strdup(envp[j]);
		if (!copy[j])
		{
			while (--j >= 0)
				free (copy[j]);
			return (free (copy[i]), free (copy), NULL);
		}
	}
	return (copy);
}

void	clean_env(t_env *env)
{
	int	i;
	
	i = 0;
	if (env->env_current && env->env_current[i])
	{
		while (env->env_current[i])
			free (env->env_current[i++]);
		free (env->env_current);
	}
	i = 0;
	if (env->export_current && env->export_current[i])
	{
		while (env->export_current[i])
			free (env->export_current[i++]);
		free (env->export_current);
	}
	i = 0;
	if (env->cmd_paths && env->cmd_paths[i])
	{
		while (env->cmd_paths[i])
			free(env->cmd_paths[i++]);
		free(env->cmd_paths);
	}
}
