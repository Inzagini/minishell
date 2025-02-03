#ifndef EXECUTOR_H
# define EXECUTOR_H

# define PATH_MAX 4096

typedef struct s_executor_data
{
	int		pipefd[2][2];
	pid_t	pid;
	int		in_fd;
	int		out_fd;
	int		rd_in;
	int		status;
}	t_exdat;

typedef struct s_heredoc
{
	char	*delimiter;
	int		pipefd[2];
	char	*line;
	char	*expanded;
	struct sigaction	sa_old;
	struct sigaction	sa_new;
}	t_here_doc;

void	executor_init(t_exdat *data);
void	executor(t_command *cmd_list, t_env *env);
int		call_pipe_line(t_command **cmd_lst, t_env *env, t_exdat *data);
void	execute_build_in(t_command *cmd, t_env *env);

void	invoke_builtin(t_command *cmd, t_env *env);
void	call_execve(t_command *data, t_env *env);

//build_in functions
void	call_builtin(t_command *cmd, t_env *env);
void	ft_echo(t_command *cmd, t_env *env);
void	ft_pwd(t_env *env);
void	ft_cd(t_command *cmd, t_env *env);
void	update_pwd(t_env *env);
void	ft_export(t_command *cmd, t_env *env);
void	ft_exit(t_command *cmd, t_env *env);
void	ft_env(t_command *cmd, t_env *env);
void	ft_unset(t_command *cmd, t_env *env);

int		ft_strcmp(char *s1, char *s2);

//redirect funcs
int		redirect_in_handle(t_command *cmd_node, t_exdat *data, t_env *env);
int		redirect_out_handle(t_command *cmd_node, t_exdat *data, t_env *env);

//pipes
void	close_all_pipes(int pipefd[2][2]);
void	close_parent_pipes(t_command *cmd_lst, int pipefd[2][2]);
void	close_child_pipes(t_command *cmd_lst, int pipefd[2][2]);

//supp
int		lst_len(t_command *lst);
void	print_err(char *prefix, char *msg, char *name);
void	print_err_long(char *prefix, char *function, char *msg, char *attrib);
char	*ft_get(char *name, char **env);
int		ft_wiexitstatus(int status);
int		exit_check(t_env *env);

//build-in export functions
void	check_add_vars(t_command *cmd, t_env *env, int i);
void	print_export(t_env	*env);
void	sort_export(t_env *env);
int		check_options(char **args);
int		check_argument(char *arg);
int		find_argument(char *var, char **env);
int		append_to_end(char *var, char ***list);
char	*add_quotes(char *arg);
int		export_to_exp(char *arg, t_env *env);
int		export_to_env(char *arg, t_env *env);

#endif
