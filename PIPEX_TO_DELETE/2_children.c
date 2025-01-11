/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_children.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:31:40 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/19 11:41:43 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(int index, t_pipex pipex, char **envp)
{
	ft_redirect(&pipex, index, envp);
	ft_close_pipes(&pipex);
	pipex.cmd_args = ft_split(pipex.av[index + 2], ' ');
	pipex.cmd = ft_get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		ft_msg_invalid_command(&pipex, envp, index);
		ft_free_pipex_children(&pipex);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
	ft_free_pipex_children(&pipex);
	ft_msg_exit(&pipex, envp);
	exit(1);
}

void	ft_redirect(t_pipex *pipex, int index, char **envp)
{
	if (index == 0)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			ft_cleanup_and_exit(pipex, envp, pipex->ac - 4);
		if (dup2(pipex->pipes[index][1], STDOUT_FILENO) == -1)
			ft_cleanup_and_exit(pipex, envp, pipex->ac - 4);
	}
	else if (index == pipex->ac - 4)
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			ft_handle_outfile(pipex, envp);
		if (dup2(pipex->pipes[index - 1][0], STDIN_FILENO) == -1)
			ft_cleanup_and_exit(pipex, envp, pipex->ac - 4);
	}
	else
	{
		if (dup2(pipex->pipes[index][1], STDOUT_FILENO) == -1)
			ft_cleanup_and_exit(pipex, envp, pipex->ac - 4);
		if (dup2(pipex->pipes[index - 1][0], STDIN_FILENO) == -1)
			ft_cleanup_and_exit(pipex, envp, pipex->ac - 4);
	}
}

void	ft_handle_outfile(t_pipex *pipex, char **envp)
{
	if (access(pipex->av[pipex->ac - 1], W_OK) == -1)
	{
		ft_msg_no_exit(pipex, envp);
		ft_free_cmd_paths(pipex);
		ft_close_pipes(pipex);
		exit(1);
	}
	ft_cleanup_and_exit(pipex, envp, pipex->ac - 4);
}
