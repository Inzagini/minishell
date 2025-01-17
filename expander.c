#include "minishell.h"

t_command	*expander(t_command *cmd_list, char **envp, t_env *env)
{
	check_builtins(cmd_list);
	expand_tilde(env, cmd_list);
	expand_question(env, cmd_list);
	expand_arguments_dquote(env, cmd_list);
	t_command *temp = cmd_list;
	while (cmd_list)
	{
		print_command(cmd_list);
		cmd_list = cmd_list->next;
	}
	cmd_list = temp;
	expand_arguments_noquote(env, cmd_list);
	temp = cmd_list;
	while (cmd_list)
	{
		print_command(cmd_list);
		cmd_list = cmd_list->next;
	}
	cmd_list = temp;
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
		if (ft_strcmp(arg, "echo") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "cd") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "pwd") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "export") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "unset") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "env") == 0)
			cmd_list->builtin_flag = 1;
		else if (ft_strcmp(arg, "exit") == 0)
			cmd_list->builtin_flag = 1;
		cmd_list = cmd_list->next;
	}
}

