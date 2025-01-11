/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_clean_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:25:11 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/18 16:50:18 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_pipex_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	ft_close_files(pipex);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

void	ft_free_pipex_children(t_pipex *pipex)
{
	int	i;

	i = 0;
	ft_close_files(pipex);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
	i = 0;
	if (pipex->cmd_args)
	{
		while (pipex->cmd_args[i])
		{
			free(pipex->cmd_args[i]);
			i++;
		}
		free(pipex->cmd_args);
	}
}

void	ft_close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->ac - 4))
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
}

void	ft_close_files(t_pipex *pipex)
{
	if (pipex->infile > 0)
		close(pipex->infile);
	if (pipex->outfile > 0)
		close(pipex->outfile);
}

void	ft_free_cmd_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}
