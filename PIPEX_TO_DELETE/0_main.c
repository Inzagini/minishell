/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:42:30 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/19 11:34:06 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		i;

	ft_initialize_pipex(&pipex, envp, ac, av);
	if (pipex.ac < 5)
		return (ft_msg_no_exit(&pipex, envp));
	ft_initialize_pipes(&pipex, envp);
	i = -1;
	while (++i < (ac - 3))
	{
		pipex.pid1 = fork();
		if (pipex.pid1 == 0)
			ft_child_process(i, pipex, envp);
	}
	ft_close_pipes(&pipex);
	ft_free_pipex_parent(&pipex);
	ft_exit_check(ac - 3);
	return (0);
}

void	ft_initialize_pipex(t_pipex *pipex, char **envp, int ac, char **av)
{
	pipex->ac = ac;
	pipex->av = av;
	pipex->cmd = NULL;
	pipex->full_path = ft_find_path(envp, pipex);
	pipex->cmd_paths = ft_split(pipex->full_path, ':');
	if (!pipex->cmd_paths)
		ft_msg_exit(pipex, envp);
	pipex->infile_error = 0;
}

void	ft_initialize_pipes(t_pipex *pipex, char **envp)
{
	int	i;

	i = -1;
	pipex->infile = open(pipex->av[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		pipex->infile_error = 1;
		ft_msg_no_exit(pipex, envp);
		pipex->infile = open("/dev/null", O_RDONLY);
	}
	pipex->outfile = open(pipex->av[pipex->ac - 1], O_TRUNC
			| O_CREAT | O_WRONLY, 0644);
	pipex->pipes = malloc ((pipex->ac - 4) * sizeof(int *));
	if (!pipex->pipes)
		ft_cleanup_and_exit(pipex, envp, i);
	while (++i < (pipex->ac - 4))
	{
		pipex->pipes[i] = malloc(2 * sizeof(int));
		if (!pipex->pipes[i])
			ft_cleanup_and_exit(pipex, envp, i);
		if (pipe(pipex->pipes[i]) < 0)
			ft_cleanup_and_exit(pipex, envp, i);
	}
}
