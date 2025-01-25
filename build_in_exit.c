#include "minishell.h"

int	is_allnums(char *str);
int	ft_atouc(char *str);

//exit don't clean yet
void	ft_exit(t_command *cmd, t_env *env)
{
	int	status;

	if (cmd->args[1] != NULL)
	{
		if (cmd->args[2] != NULL)
		{
			print_err(ft_get("SHELL", env->env), "too many arguments", "exit");
			return ;
		}
		else if (is_allnums(cmd->args[1]))
		{
			print_err(ft_get("SHELL", env->env),
				"numeric argument required", NULL);
			env->last_exit_status = 2;
		}
	}
	if (cmd->args[1])
		status = ft_atouc(cmd->args[1]);
	else
		status = env->last_exit_status;
	printf("exit\n");
	clean_env(env);
	clean_commands(cmd);
	rl_clear_history();
	exit(status);
}

int	is_allnums(char *str)
{
	int	index;

	index = -1;
	if (str[0] == '+' || str[0] == '-')
		index++;
	while (str[++index])
	{
		printf("%d| %c\n", index, str[index]);
		if (str[index] < '0' || str[index] > '9')
			return (1);
	}
	return (0);
}

int	ft_atouc(char *str)
{
	unsigned char	result;
	int				index;
	int				sign;

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
	return ((int) (sign * result));
}
