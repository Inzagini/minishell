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

void	executor_init(t_exdat *data);
int		executor(t_command *cmd_lst, t_env *env);
void	execute_build_in(t_command *cmd, t_env *env);

//build_in functions
void	call_build_in(t_command *cmd, t_env *env);
void	ft_echo(t_command *cmd, t_env *env);
void	ft_pwd(t_command *cmd, t_env *env);
void	ft_cd(t_command *cmd, t_env *env);
void	ft_export(t_command *cmd, t_env *env);
void	ft_exit(t_command *cmd, t_env *env);

//redirect funcs
int	redirect_in_handle(t_command *cmd_node, t_exdat *data);
int	redirect_out_handle(t_command *cmd_node, t_exdat *data);

//pipes
void	close_all_pipes(int pipefd[2][2]);
void	close_parent_pipes(t_command *cmd_lst, int pipefd[2][2]);
void	close_child_pipes(t_command *cmd_lst, int pipefd[2][2]);

//supp
int		lst_len(t_command *lst);
void	print_error(char *prefix, char *msg, char *name);
char	*ft_getenv(char *name, char **env);
void	exit_check(int n_cmd);
#endif
