/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:43 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/05 16:38:20 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*set_empty_arg(t_command *cmd, int i);

t_command	*expander(t_command *cmd_list, t_env *env)
{
	expand_tilde(env, cmd_list);
	expand_special(env, cmd_list);
	expand_arguments_dquote(env, cmd_list);
	expand_arguments_noquote(env, cmd_list);
	merge_arguments(cmd_list);
	remove_empty_arguments(cmd_list);
	check_builtins(cmd_list);
	expand_commands(env, cmd_list);
	return (NULL);
}

void	remove_empty_arguments(t_command *cmd_list)
{
	int			i;
	int			j;

	while (cmd_list)
	{
		i = 0;
		while (cmd_list->args[i])
		{
			if (!cmd_list->args[i][0] && cmd_list->quotes[i] == 0)
			{
				free(cmd_list->args[i]);
				j = i;
				while (cmd_list->args[j + 1])
				{
					cmd_list->args[j] = cmd_list->args[j + 1];
					cmd_list->quotes[j] = cmd_list->quotes[j + 1];
					j++;
				}
				cmd_list->args[j] = NULL;
				continue ;
			}
			i++;
		}
		cmd_list = set_empty_arg(cmd_list, i);
	}
}

static t_command	*set_empty_arg(t_command *cmd, int i)
{
	if (i == 0 && cmd->quotes[0] == 0)
		cmd->args[0] = ft_strdup("");
	else if (!cmd->args[0][0] && cmd->quotes[0] == 2)
	{
		free (cmd->args[0]);
		cmd->args[0] = NULL;
	}
	cmd = cmd->next;
	return (cmd);
}

void	check_builtins(t_command *cmd_list)
{
	char	*arg;

	while (cmd_list)
	{
		arg = cmd_list->args[0];
		if (ft_strcmp(arg, "echo") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "cd") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "pwd") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "export") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "unset") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "env") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "exit") == 0)
			cmd_list->builtin_flag = 1;
		cmd_list = cmd_list->next;
	}
}
