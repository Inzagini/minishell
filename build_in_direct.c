/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_direct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:42:26 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/06 14:35:56 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_free(char *pwd, char *old_pwd, t_env *env);

void	ft_pwd(t_env *env)
{
	char	buff[PATH_MAX];
	char	*path;

	path = getcwd(buff, PATH_MAX);
	printf("%s\n", path);
	env->last_exit_status = 0;
}

void	ft_cd(t_command *cmd, t_env *env)
{
	env->last_exit_status = 0;
	if (cmd->args[1] == NULL)
	{
		if (ft_get("HOME", env->env) == NULL)
			print_err(ft_get("SHELL", env->env),
				cmd->args[0], "HOME not set");
		else
			print_err(ft_get("SHELL", env->env),
				ft_get("HOME", env->env), "No such file or directory");
		env->last_exit_status = 1;
	}
	else if (cmd->args[2] != NULL)
	{
		print_err(ft_get("SHELL", env->env),
			"too many arguments", "cd");
		env->last_exit_status = 1;
	}
	else if (chdir(cmd->args[1]) == -1)
	{
		print_err(ft_get("SHELL", env->env),
			strerror(errno), cmd->args[1]);
		env->last_exit_status = 1;
	}
	update_pwd(env);
	return ;
}

void	update_pwd(t_env *env)
{
	char	*pwd;
	char	*old_pwd;
	char	*get_cwd;

	get_cwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", get_cwd);
	free (get_cwd);
	if (!pwd)
	{
		print_err(ft_get("SHELL", env->env),
			"update pwd failed", NULL);
		env->last_exit_status = 1;
		return ;
	}
	old_pwd = ft_strjoin("OLDPWD=", ft_get("PWD", env->env));
	if (!old_pwd)
	{
		print_err(ft_get("SHELL", env->env),
			"update pwd failed", NULL);
		env->last_exit_status = 1;
		free (pwd);
		return ;
	}
	export_free(pwd, old_pwd, env);
}

static void	export_free(char *pwd, char *old_pwd, t_env *env)
{
	export_to_env(pwd, env);
	export_to_exp(pwd, env);
	export_to_env(old_pwd, env);
	export_to_exp(old_pwd, env);
	free (pwd);
	free (old_pwd);
}
