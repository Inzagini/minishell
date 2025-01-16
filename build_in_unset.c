#include "minishell.h"

void	unset_variable(char *arg, char **array);
int		check_options_unset(char **args);

void	ft_unset(t_command *cmd, t_env *env)
{
	int		i;

	if (cmd->args[1] == 0)
		return ;
	i = check_options_unset(cmd->args);
	if (i > 0)
	{
		printf("%s: unset: %.2s: invalid option\n", getenv("SHELL"), cmd->args[i]);
		printf("unset: usage: unset [name ...]\n");
		env->last_exit_status = 2;
		return ;
	}
	while (cmd->args[++i])
	{
		unset_variable(cmd->args[i], env->env_current);
		unset_variable(cmd->args[i], env->export_current);
	}
}

void	unset_variable(char *arg, char **array)
{
	int	i;
	int	len;

	if (!array || !array[0] || !arg)
		return ;
	i = -1;
	len = ft_strlen(arg);
	while (array[++i])
	{
		if (ft_strncmp(array[i], arg, len) == 0
			&& (array[i][len] == '\0'
			|| array[i][len] == '='))
		{
			free (array[i]);
			while (array[i + 1])
			{
				array[i] = array[i + 1];
				i++;
			}
			array[i] = 0;
		}
	}
}

int	check_options_unset(char **args)
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
