/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:35 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/07 16:47:37 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*command;
	char	**cmd_paths;
	char	*full_path;

	full_path = find_path(env->env);
	if (!full_path)
		return ;
	cmd_paths = ft_split(full_path, ':');
	if (!cmd_paths)
		return ;
	while (cmd_list)
	{
		if (cmd_list->builtin_flag == 0 && cmd_list->args[0]
			&& cmd_list->args[0][0])
		{
			command = get_cmd(cmd_paths, cmd_list->args[0]);
			if (command)
			{
				free (cmd_list->args[0]);
				cmd_list->args[0] = command;
			}
		}
		cmd_list = cmd_list->next;
	}
	free_split(cmd_paths);
}

void	expand_commands_post(t_env *env, t_command *cmd_list)
{
	char	*command;

	while (cmd_list)
	{
		if (cmd_list->builtin_flag == 0)
		{
			command = get_cmd(env->cmd_paths, cmd_list->arg_tokens->content);
			if (command)
			{
				free (cmd_list->arg_tokens->content);
				cmd_list->arg_tokens->content = command;
			}
		}
		cmd_list = cmd_list->next;
	}
}
