/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_envp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:27:52 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/18 10:31:29 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_path(char **envp, t_pipex *pipex)
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
	{
		ft_msg_no_exit(pipex, envp);
		ft_close_pipes(pipex);
		ft_close_files(pipex);
		exit(1);
	}
	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	return (envp[i] + 5);
}

char	*ft_get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}
