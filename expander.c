#include "minishell.h"

/*
    - DONE get environment variables and save copy?
    - DONE get execution path + save in cmd_paths with split
    - DONE check command name and replace args[0]
    - DONE test with access stand_alone
    - DONE test with access and all available commands
    - DONE save working command in args[0] or input if none found
    - DONE hanlde built-ins -> do nothing
    - check if $ found
        -> if no brackets after dollar sign -> expand variable and replace (depending on SQuotes and DQuotes)
            if no_quotes -> split at Whitespaces and into separate arguemnts
            if SQOTES -> do not expand
            if DQUOTES -> expand into single argument
        -> if brackets -> command substitution process
    - check if ~ is found -> replace with home directory

   if no quotes at all
     find $ -> split here
     find next non-alphnumeric/non_underscore ->split here
     take middle section and replace with env variable (none if not found)
     take back together as single argument
     for all
*/

t_command   *expander(t_command *cmd_list, char **envp, t_env *env)
{
	t_command   *curr_cmd;

	if (copy_envp(env, envp) == 1)
		return (NULL);
	env->full_path = find_path(env->env_current);
	env->cmd_paths = ft_split(env->full_path, ':');
	if (!env->cmd_paths)
		return (NULL);
	check_builtins(cmd_list);
	expand_arguments(env, cmd_list);
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

