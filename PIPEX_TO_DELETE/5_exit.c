/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:49:26 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/19 09:47:41 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_exit_check(int n_cmd)
{
	int		i;
	int		last_status;
	int		status;
	pid_t	*pid_array;
	int		*status_array;

	i = -1;
	status = 0;
	status_array = malloc (sizeof(int) * n_cmd);
	if (!status_array)
		return (1);
	pid_array = malloc (sizeof(pid_t) * n_cmd);
	if (!pid_array)
		return (free (status_array), 1);
	last_status = ft_determine_exit(n_cmd, pid_array, status_array, status);
	free (status_array);
	free (pid_array);
	exit(last_status);
}

int	ft_determine_exit(int n_cmd, int *pid_arr, int *status_arr, int status)
{
	int	pid_max;
	int	last_status;
	int	i;

	i = -1;
	while (++i < n_cmd)
	{
		pid_arr[i] = wait(&status);
		if (pid_arr[i] == -1)
			return (free(pid_arr), free(status_arr), 1);
		status_arr[i] = WEXITSTATUS(status);
	}
	i = -1;
	pid_max = 0;
	while (++i < n_cmd)
	{
		if (pid_arr[i] > pid_max)
		{
			pid_max = pid_arr[i];
			last_status = status_arr[i];
		}
	}
	return (last_status);
}

void	ft_cleanup_and_exit(t_pipex *pipex, char **envp, int index)
{
	int	i;

	i = 0;
	if (index < pipex->ac - 4)
		pipex->ac = index;
	while (i < pipex->ac - 4)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		free(pipex->pipes[i]);
		i++;
	}
	if (index != -1)
		free(pipex->pipes);
	ft_free_pipex_parent(pipex);
	ft_msg_exit(pipex, envp);
}
