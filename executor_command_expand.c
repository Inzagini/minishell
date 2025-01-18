#include "minishell.h"

char *get_cmd_expan_arg(t_command **cmd_lst, t_env *env)
{
	t_exdat	data;
	int		finalfd;
	char	*line;

	executor_init(&data);
	while ((*cmd_lst))
	{
		if ((*cmd_lst)->id != 0)
			pipe(data.pipefd[((*cmd_lst)->id + 1) % 2]);
		env->child_pid = fork();
		if (env->child_pid == 0)
		{
			pre_handle((*cmd_lst), &data);
			if ((*cmd_lst)->builtin_flag)
				invoke_builtin((*cmd_lst), env);
			else
				call_execve((*cmd_lst), env);
		}
		close_parent_pipes((*cmd_lst), data.pipefd);
		(*cmd_lst) = (*cmd_lst)->next;
	}
	finalfd = data.pipefd[((*cmd_lst)->id + 1) % 2][0];
	close_all_pipes(data.pipefd);
	return (line);
}

char *read_alloc(int fd)
{
	char *line = ft_get_next_line(fd);
	printf("line: %s\n", line);
	return (line);
}
