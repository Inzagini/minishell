/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:22 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 14:51:40 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_command *cmd_list, t_env *env)
{
	t_exdat		*data;
	t_command	*head;

	data = malloc(sizeof(t_exdat));
	head = cmd_list;
	if (!data || executor_init(data) == -1)
	{
		free(data);
		data = NULL;
		return ;
	}
	while (cmd_list)
	{
		if (cmd_list->builtin_flag && cmd_list->redir_out != 3
			&& cmd_list->redir_in != 3)
		{
			execute_build_in(cmd_list, env, data, head);
			cmd_list = cmd_list->next;
		}
		else
			env->last_exit_status = call_pipe_line(&cmd_list, env, data, head);
	}
	free(data);
	data = NULL;
}

int	executor_init(t_exdat *data)
{
	if (pipe(data->pipefd[0]))
		return (-1);
	data->in_fd = 0;
	data->out_fd = 1;
	data->rd_in = 0;
	return (0);
}
