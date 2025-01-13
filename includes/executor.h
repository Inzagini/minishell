#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>


typedef struct s_executor_data
{
	int	pipefd[2][2];
	pid_t	pid;
	int		in_fd;
	int		out_fd;

}	t_exdat;

int		executor(t_command *lst_cmd);

//built_in functions
void	ft_echo(t_command *cmd);

//supp
int		lst_len(t_command *lst);
void	print_error(char *prefix, char *msg, char *name);

//redirect funcs
int	redirect_in_handle(t_command *cmd_node, int pipefd[2][2]);
int	redirect_out_handle(t_command *cmd_node, int pipefd[2][2]);

//pipes
void	close_all_pipes(int pipefd[2][2]);
void	close_parent_pipes(t_command *lst_cmd, int pipefd[2][2]);
void	close_child_pipes(t_command *lst_cmd, int pipefd[2][2]);
#endif
