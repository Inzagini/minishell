/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:42:50 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:42:51 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_to_end(char *var, char ***list)
{
	int		i;
	int		j;
	char	**new_list;

	i = 0;
	if (!var || !list || !*list)
		return (1);
	while ((*list)[i])
		i++;
	new_list = malloc((i + 2) * sizeof(char *));
	if (!new_list)
		return (1);
	j = -1;
	while (++j < i)
		new_list[j] = (*list)[j];
	new_list[i] = var;
	new_list[i + 1] = NULL;
	free(*list);
	*list = new_list;
	return (0);
}

int	find_argument(char *var, char **env)
{
	size_t	len_var;
	size_t	i;
	char	*end;
	char	*env_eq;

	i = -1;
	end = ft_strchr(var, '=');
	if (end != NULL)
		len_var = end - var;
	else
		len_var = ft_strlen(var);
	while (env[++i])
	{
		env_eq = ft_strchr(env[i], '=');
		if (env_eq != NULL)
		{
			if (ft_strncmp(env[i], var, len_var) == 0 && env[i][len_var] == '=')
				return (i);
		}
		else
			if (ft_strncmp(env[i], var, len_var) == 0)
				return (i);
	}
	return (-1);
}

int	check_argument(char *arg)
{
	size_t	i;
	size_t	j;
	char	*ok;

	ok = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	i = 0;
	if (arg[0] >= '0' && arg[0] <= '9')
		return (1);
	while (arg[i])
	{
		j = 0;
		if (i > 0 && arg[i] == '=')
			break ;
		while (ok[j])
		{
			if (arg[i] == ok[j])
				break ;
			j++;
		}
		if (j == 63)
			return (1);
		i++;
	}
	return (0);
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

void	print_export(t_env *env)
{
	int		i;
	char	*temp;

	i = 0;
	while (env->exp[i] && env->exp[i + 1])
	{
		if (ft_strncmp(env->exp[i]
				, env->exp[i + 1], 1024) > 0)
		{
			temp = env->exp[i];
			env->exp[i] = env->exp[i + 1];
			env->exp[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	i = -1;
	while (env->exp[++i])
		printf("declare -x %s\n", env->exp[i]);
}
