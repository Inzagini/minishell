#include "minishell.h"

int	is_allnums(char *str);
unsigned char	ft_atouc(char *str);

//exit don't clean yet
void	ft_exit(t_command *cmd, t_env *env)
{
	if (cmd->args[1] != NULL)
	{
		if (cmd->args[2] != NULL)
		{
			print_error(ft_getenv("SHELL", env->env_current), "too many arguments", "exit");
		}
		else if (is_allnums(cmd->args[1]))
		{
			print_error(ft_getenv("SHELL", env->env_current), "numeric argument required", cmd->args[1]);
			exit(2);
		}
		else if (cmd->args[1])
		{
			printf("exit\n");
			clean_env(env);
			clean_commands(cmd);
			exit(ft_atouc(cmd->args[1]));
		}
	}
	else
	{
		printf("exit\n");
		clean_env(env);
		clean_commands(cmd);
		exit(env->last_exit_status);
	}
}

int	is_allnums(char *str)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (str[index] < '1' || str[index] > '9')
			return (1);
	}
	return (0);
}

unsigned char	ft_atouc(char *str)
{
	unsigned char	result;
	int		index;

	result = 0;
	index = -1;
	while(str[++index])
		result = result * 10 + str[index] - '0';
	return (result);
}
