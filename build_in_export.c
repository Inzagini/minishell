#include "minishell.h"

void	ft_export(t_command *cmd, t_env *env)
{
/*
	+ append to env_current

	call without arguments -> show all variables in env as declare -x VAR="abc"

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
		add/replace valid arguments in env
		print error message if invalid var_name found
		exit with correct exit code (0 if all good)

*/




}
