#include "minishell.h"

static int	pre_handle(t_command *cmd, t_exdat *data, t_env *env);

int	call_pipe_line(t_command **cmd_lst, t_env *env)
{
	t_exdat	data;

	executor_init(&data);
	while ((*cmd_lst))
	{
		if ((*cmd_lst)->id != 0)
			pipe(data.pipefd[((*cmd_lst)->id + 1) % 2]);
		env->child_pid = fork();
		// printf("creating child %d\n", env->child_pid);
		if ((*cmd_lst)->id != 0 && env->child_pid != 0)
		{
			// printf("IN| %d wait for %d\n", env->child_pid,wait(NULL));
			wait(NULL);
			// printf("IN| %d wait for %d\n", env->child_pid,waitpid(env->prev_pid, NULL, 0));
		}
		if (env->child_pid == 0)
		{
			if (pre_handle((*cmd_lst), &data, env))
			{
				(*cmd_lst) = (*cmd_lst)->next;
				break ;
			}
			if ((*cmd_lst)->builtin_flag)
				invoke_builtin((*cmd_lst), env);
			else
				call_execve((*cmd_lst), env);
		}
		if ((*cmd_lst)->redir_in == 2)
			waitpid(env->child_pid, NULL, 0);
		// 	printf("IN| %d wait for %d\n", env->child_pid,waitpid(env->child_pid, NULL, 0));
		env->prev_pid = env->child_pid;
		close_parent_pipes((*cmd_lst), data.pipefd);
		(*cmd_lst) = (*cmd_lst)->next;
		if ((*cmd_lst) && (*cmd_lst)->redir_in == 0)
		 	break ;
	}
	close_all_pipes(data.pipefd);
	return (0);
}


void	invoke_builtin(t_command *cmd, t_env *env)
{
	call_builtin(cmd, env);
	exit(env->last_exit_status);
}

void	call_execve(t_command *data, t_env *env)
{
	if (!data->args || !data->args[0])
	{
		print_err(ft_get("SHELL", env->env), "command not found", NULL);
		exit(127);
	}
	if (!data->args[0][0])
		exit(0);
	execve(data->args[0], data->args, env->env);
	if (ft_strchr(data->args[0], '/'))
	{
		if (errno == ENOENT)
		{
			print_err(ft_get("SHELL", env->env), "No such file or directory", data->args[0]);
			exit(127);
		}
		else if (errno == EISDIR)
		{
			print_err(ft_get("SHELL", env->env), "Is a directory", data->args[0]);
			exit(126);
		}
		else if (errno == EACCES)
		{
			print_err(ft_get("SHELL", env->env), "Permission denied", data->args[0]);
			exit(126);
		}
		else
		{
			print_err(ft_get("SHELL", env->env), strerror(errno), data->args[0]);
			exit(1);
		}
	}
	else
	{
		print_err(ft_get("SHELL", env->env), "command not found", data->args[0]);
		exit(127);
	}
}


void	executor_init(t_exdat *data)
{
	pipe(data->pipefd[0]);
	pipe(data->pipefd[1]);
	data->in_fd = 0;
	data->out_fd = 1;
}

static int	pre_handle(t_command *cmd, t_exdat *data, t_env *env)
{
	if (redirect_in_handle(cmd, data, env))
		return (close_child_pipes(cmd, data->pipefd), exit (1), 1);
	if (redirect_out_handle(cmd, data, env))
		return (close_child_pipes(cmd, data->pipefd), exit (1), 1);
	close_child_pipes(cmd, data->pipefd);
	return (0);
}
