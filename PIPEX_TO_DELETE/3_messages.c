/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_messages.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 12:57:23 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/19 11:40:05 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_msg_invalid_command(t_pipex *pipex, char **envp, int index)
{
	if (pipex->infile_error == 1 && index == 0)
		return (1);
	ft_dprintf("%s: %s: %s\n", ft_get_shell(envp),
		"command not found", pipex->cmd_args[0]);
	return (1);
}

int	ft_msg_no_exit(t_pipex *pipex, char **envp)
{
	if (pipex->ac < 5)
	{
		ft_free_cmd_paths(pipex);
		ft_dprintf("Too few arguments in input\n");
	}
	else if ((errno == 2 || errno == 13) && pipex->infile < 0)
		ft_dprintf("%s: %s: %s\n", ft_get_shell(envp),
			strerror(errno), pipex->av[1]);
	else if ((errno == 2 || errno == 13) && pipex->infile > 0)
		ft_dprintf("%s: %s: %s\n", ft_get_shell(envp),
			strerror(errno), pipex->av[pipex->ac - 1]);
	else
		ft_dprintf("%s: %s\n", ft_get_shell(envp), strerror(errno));
	return (1);
}

void	ft_msg_exit(t_pipex *pipex, char **envp)
{
	if (errno == 13)
		ft_dprintf("%s: %s: %s\n", ft_get_shell(envp), strerror(errno),
			& pipex->av[pipex->ac - 1]);
	else
		ft_dprintf("%s: %s:\n", ft_get_shell(envp), strerror(errno));
	exit(errno);
}

char	*ft_get_shell(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("SHELL=", envp[i], 6))
		i++;
	return (envp[i] + 11);
}
