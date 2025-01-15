#include "minishell.h"

t_command	*expander(t_command *cmd_list, char **envp, t_env *env)
{
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

		arg = cmd_list->arg_tokens->content;
		if (ft_strncmp(arg, "echo", 4) == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strncmp(arg, "cd", 2) == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strncmp(arg, "pwd", 3) == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strncmp(arg, "export", 6) == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strncmp(arg, "unset", 5) == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strncmp(arg, "env", 3) == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strncmp(arg, "exit", 4) == 0)
			cmd_list->builtin_flag = 1;
		cmd_list = cmd_list->next;
	}
}

