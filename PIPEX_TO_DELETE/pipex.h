/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:47:36 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/19 11:36:25 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_pipex
{
	pid_t	pid1;
	int		ac;
	char	**av;
	int		infile;
	int		outfile;
	int		**pipes;
	char	*full_path;
	char	**cmd_paths;
	char	*cmd;
	char	**cmd_args;
	int		infile_error;
}			t_pipex;

int		main(int ac, char **av, char **envp);
void	ft_initialize_pipex(t_pipex *pipex, char **envp, int ac, char **av);
void	ft_initialize_pipes(t_pipex *pipex, char **envp);

char	*ft_find_path(char **envp, t_pipex *pipex);
char	*ft_get_cmd(char **paths, char *cmd);

void	ft_child_process(int index, t_pipex pipex, char **envp);
void	ft_redirect(t_pipex *pipex, int index, char **envp);
void	ft_handle_outfile(t_pipex *pipex, char **envp);

void	ft_msg_exit(t_pipex *pipex, char **envp);
int		ft_msg_no_exit(t_pipex *pipex, char **envp);
int		ft_msg_invalid_command(t_pipex *pipex, char **envp, int index);
char	*ft_get_shell(char **envp);

void	ft_close_pipes(t_pipex *pipex);
void	ft_close_files(t_pipex *pipex);
void	ft_free_pipex_parent(t_pipex *pipex);
void	ft_free_pipex_children(t_pipex *pipex);
void	ft_free_cmd_paths(t_pipex *pipex);

int		ft_exit_check(int n_cmd);
int		ft_determine_exit(int n_cmd, int *pid_arr, int *status_arr, int status);
void	ft_cleanup_and_exit(t_pipex *pipex, char **envp, int index);

int		ft_dprintf(const char *input, ...);
int		ft_dprintf_helper(int *i, va_list *ap, const char *input);
int		ft_dprint_string(va_list *ap);

#endif
