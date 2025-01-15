#include "minishell.h"

int	ft_strcmp(char *s1, char *s2);

void	execute_build_in(t_command *cmd, t_env *env)
{
	t_exdat	data;
	int	origin_in;
	int	origin_out;

	origin_in = dup(STDIN_FILENO);
	origin_out = dup(STDOUT_FILENO);
	executor_init(&data);
	redirect_in_handle(cmd, &data);
	redirect_out_handle(cmd, &data);
	close_child_pipes(cmd, data.pipefd);
	call_build_in(cmd, env);
	close(data.pipefd[1 - ((cmd->id + 1) % 2)][1]);
	if (origin_in != -1)
	{
		dup2(origin_in, STDIN_FILENO);
		close(origin_in);
	}
	if (origin_out != -1)
	{
		dup2(origin_out, STDOUT_FILENO);
		close(origin_out);
	}
}

void	call_build_in(t_command *cmd, t_env *env)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		printf("unsupport\n");
	else if (!ft_strcmp(cmd->args[0], "env"))
		printf("unsupport\n");
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd, env);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	index;

	index = 0;
	while (s1[index] == s2[index] && (s1[index] || s2[index]))
		index++;
	return (s1[index] - s2[index]);
}
