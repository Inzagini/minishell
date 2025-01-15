#ifndef EXECUTOR_H
# define EXECUTOR_H

# define PATH_MAX 4096


typedef struct s_executor_data
{
	int	pipefd[2][2];
	pid_t	pid;
	int		in_fd;
	int		out_fd;

}	t_exdat;

int		executor(t_command *lst_cmd);

//build_in functions
void	call_build_in(t_command *cmd, t_env *env);
void	ft_echo(t_command *cmd);
void	ft_pwd(t_command *cmd);
void	ft_cd(t_command *cmd);
void	ft_export(t_command *cmd, t_env *env);
void	ft_exit(t_command *cmd, t_env *env);

//supp
int		lst_len(t_command *lst);
void	print_error(char *prefix, char *msg, char *name);
char	*ft_getenv(char *name, char **env);

//redirect funcs
int	redirect_in_handle(t_command *cmd_node, t_exdat *data);
int	redirect_out_handle(t_command *cmd_node, t_exdat *data);

//pipes
void	close_all_pipes(int pipefd[2][2]);
void	close_parent_pipes(t_command *lst_cmd, int pipefd[2][2]);
void	close_child_pipes(t_command *lst_cmd, int pipefd[2][2]);
#endif
