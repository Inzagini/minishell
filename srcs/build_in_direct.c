/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_direct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:42:26 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/06 15:59:39 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_free(char *pwd, char *old_pwd, t_env *env);
static void	cd_error(t_env *env, char *msg1, char *msg2);

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
			cd_error(env, cmd->args[0], "HOME not set");
		else if (chdir(ft_get("HOME", env->env)) == -1)
			cd_error(env, ft_get("HOME", env->env),
				"No such file or directory");
	}
	else if (cmd->args[2] != NULL)
		cd_error(env, "too many arguments", "cd");
	else if (chdir(cmd->args[1]) == -1)
		cd_error(env, strerror(errno), cmd->args[1]);
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

static void	cd_error(t_env *env, char *msg1, char *msg2)
{
	print_err(ft_get("SHELL", env->env), msg1, msg2);
	env->last_exit_status = 1;
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
