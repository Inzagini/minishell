#include "minishell.h"

t_command	*expander(t_command *cmd_list, t_env *env)
{
	expand_tilde(env, cmd_list);
	expand_special(env, cmd_list);
	expand_arguments_dquote(env, cmd_list);
	expand_arguments_noquote(env, cmd_list);
	merge_arguments(cmd_list);
	remove_empty_arguments(cmd_list);
	check_builtins(cmd_list);
	expand_commands(env, cmd_list);
	return (NULL);
}

void remove_empty_arguments(t_command *cmd_list)
{
	t_command	*curr;
	int			i;
	int			j;

	curr = cmd_list;
	while (curr)
	{
		i = 0;
		while (curr->args[i])
		{
			if (!curr->args[i][0])
			{
				j = i;
				while (curr->args[j + 1])
				{
					curr->args[j] = curr->args[j + 1];
					j++;
				}
				curr->args[j] = NULL;
			}
			else
				i++;
		}
		curr = curr->next;
	}
}


void	check_builtins(t_command *cmd_list)
{
	char	*arg;

	while (cmd_list)
	{
		arg = cmd_list->args[0];
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
