#include "minishell.h"

t_command	*expander(t_command *cmd_list, char **envp, t_env *env)
{
	t_command	*curr_cmd;

	if (copy_envp(env, envp) == 1)
		return (NULL);
	env->full_path = find_path(env->env_current);
	env->cmd_paths = ft_split(env->full_path, ':');
	if (!env->cmd_paths)
		return (NULL);
	check_builtins(cmd_list);
	expand_tilde(env, cmd_list);
	expand_arguments_dquote(env, cmd_list);
	expand_arguments_noquote(env, cmd_list);
	expand_commands(env, cmd_list);
	merge_arguments(cmd_list);
	
	return (NULL);
}

void	check_builtins(t_command *cmd_list)
{
	while (cmd_list)
	{
		char	*arg;
		size_t	len;

		arg = cmd_list->arg_tokens->content;
		len = ft_strlen(arg);
		if (ft_strncmp(arg, "echo", len) == 0)
			cmd_list->builtin_flag = 1;
		if (ft_strncmp(arg, "cd", len) == 0)
			cmd_list->builtin_flag = 1;
		if (ft_strncmp(arg, "pwd", len) == 0)
			cmd_list->builtin_flag = 1;
		if (ft_strncmp(arg, "export", len) == 0)
			cmd_list->builtin_flag = 1;
		if (ft_strncmp(arg, "unset", len) == 0)
			cmd_list->builtin_flag = 1;
		if (ft_strncmp(arg, "env", len) == 0)
			cmd_list->builtin_flag = 1;
		if (ft_strncmp(arg, "exit", len) == 0)
			cmd_list->builtin_flag = 1;
		cmd_list = cmd_list->next;
	}
}

