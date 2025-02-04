/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:38 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:43:39 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->cmd_paths = NULL;
	env->env = NULL;
	env->exp = NULL;
	env->full_path = NULL;
	env->shell_name = "/bin/zsh";
	env->shell_var = "SHELL=/bin/zsh";
	env->last_exit_status = 0;
	env->env = copy_envp(envp, 0);
	if (env->env == NULL)
		return (free(env), NULL);
	env->exp = copy_envp(envp, 1);
	if (env->exp == NULL)
		return (clean_env(env), free(env), NULL);
	env->full_path = find_path(env->env);
	if (!env->full_path)
		return (clean_env(env), free(env), NULL);
	env->cmd_paths = ft_split(env->full_path, ':');
	if (!env->cmd_paths)
		return (clean_env(env), free(env), NULL);
	return (env);
}

char	**copy_envp(char **envp, int exp)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	copy = malloc ((i + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	copy[i] = 0;
	if (exp == 0)
	{
		if (copy_to_env(copy, envp, j) == 1)
			return (NULL);
	}
	else if (exp == 1)
	{
		if (copy_to_exp(copy, envp, i, j) == 1)
			return (NULL);
	}
	return (copy);
}

int	copy_to_exp(char **copy, char **envp, int i, int j)
{
	j = -1;
	while (envp[++j])
	{
		copy[j] = malloc((ft_strlen(envp[j]) + 3) * sizeof(char));
		if (!copy[j])
			return (free_split(copy), 1);
		i = 0;
		while (envp[j][i] && envp[j][i] != '=')
		{
			copy[j][i] = envp[j][i];
			i++;
		}
		copy[j][i++] = '=';
		copy[j][i++] = '"';
		while (envp[j][i - 1])
		{
			copy[j][i] = envp[j][i - 1];
			i++;
		}
		copy[j][i] = '"';
		copy[j][i + 1] = '\0';
	}
	return (0);
}

int	copy_to_env(char **copy, char **envp, int j)
{
	j = -1;
	while (envp[++j])
	{
		copy[j] = ft_strdup(envp[j]);
		if (!copy[j])
		{
			while (--j >= 0)
				free (copy[j]);
			return (free(copy), 1);
		}
	}
	return (0);
}

void	clean_env(t_env *env)
{
	int	i;

	i = 0;
	if (env->env && env->env[i])
	{
		while (env->env[i])
			free (env->env[i++]);
		free (env->env);
	}
	i = 0;
	if (env->exp && env->exp[i])
	{
		while (env->exp[i])
			free (env->exp[i++]);
		free (env->exp);
	}
	i = 0;
	if (env->cmd_paths && env->cmd_paths[i])
	{
		while (env->cmd_paths[i])
			free(env->cmd_paths[i++]);
		free(env->cmd_paths);
	}
	free (env);
}
