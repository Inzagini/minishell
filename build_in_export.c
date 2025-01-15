#include "minishell.h"

void	print_env(t_env	*env);
void	sort_env(t_env *env);
int		check_options(char **args);



void	ft_export(t_command *cmd, t_env *env)
{
/*
	+ append to env_current

	DONE call without arguments -> show all variables in env as declare -x VAR="abc"

	call with multiple arguments -> create multiple variables

 	if "-" in the very beginning of any argument -> invalid option error, do not export anything
		exit with exit code 2

	export each variable individually, print error if not valid (invalid chars) but continue with others
		exit with exit code 1 (irrespective of position)

	The name of an environment variable can only contain letters, numbers, and underscores (_), but it cannot start with a number

	pseudocode
		parse input (check for - and flag arguments that contain invalid characters)
		invalid option -> exit with exit code 2
		no arguments -> printf env with declare -x (each line)
		add/replace valid arguments in env (sort by number, large cap, small cap)
			replace: check if string before '=' or end is same, if yes, replace
		print error message if invalid var_name found
		exit with correct exit code (0 if all good)

*/
	int			i;

	i = 0;
	if (cmd->args[1] == 0)
		print_env(env);
	i = check_options(cmd->args);
	if (i > 0)
	{
		printf("%s: %s: %s: invalid option\n", getenv("SHELL"), cmd->args[0], cmd->args[i]);  // need to define path, set error message etc.
		return ;
	}
	while (++i < cmd->size)
	{
			//check for invalid option
			//	if invalid option -> error and exit code

			// loop through arguments -> if invalid -> skip and flag
			// if valid -> append
			// if flag, print error and set exit code

	}
}

int	check_options(char **args)
{
	int	i;

	i = -1;

	while (args[++i])
	{
		if (args[i][0] == '-')
			return (i);
	}
	return (0);
}

void	print_env(t_env *env)
{
	int	i;

	i = -1;
	sort_env(env);
	while (env->env_current[++i])
		printf("declare -x %s\n", env->env_current[i]);
}

void	sort_env(t_env *env)
{
	char	*temp;
	int		i;

	i = 0;
	while (env->env_current[i] && env->env_current[i + 1])
	{
		if (ft_strncmp(env->env_current[i], env->env_current[i + 1], 1024) > 0)
		{
			temp = env->env_current[i];
			env->env_current[i] = env->env_current[i + 1];
			env->env_current[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}
