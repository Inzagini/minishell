#include "minishell.h"

int	is_allnums(char *str);
int	ft_atouc(char *str);

void	ft_exit(t_command *cmd, t_env *env)
{
	if (cmd->args[1] != NULL)
	{
		if (is_allnums(cmd->args[1]) || ft_atouc(cmd->args[1]) == -1)
		{
			print_err(ft_get("SHELL", env->env),
				"numeric argument required", "exit");
			env->last_exit_status = 2;
		}
		else if (cmd->args[2] != NULL)
		{
			print_err(ft_get("SHELL", env->env), "too many arguments", "exit");
			env->last_exit_status = 1;
			return ;
		}
		else
			env->last_exit_status = ft_atouc(cmd->args[1]);
	}
	printf("exit\n");
	clean_env(env);
	clean_commands(cmd);
	rl_clear_history();
	exit(env->last_exit_status);
}

int	is_allnums(char *str)
{
	int	index;

	index = -1;
	if (str[0] == '+' || str[0] == '-')
		index++;
	while (str[++index])
	{
		if (str[index] < '0' || str[index] > '9')
			return (1);
	}
	return (0);
}

int	ft_atouc(char *str)
{
	uint64_t	result;
	int			index;
	int			sign;

	result = 0;
	index = -1;
	sign = 1;
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			sign = -1;
		index++;
	}
	while (str[++index])
		result = result * 10 + str[index] - '0';
	if (sign == -1 && (unsigned) result == 0)
		return (0);
	if (result > INT64_MAX)
		return (-1);
	result = (unsigned char) result;
	return ((int)(sign * result));
}
