/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:46:43 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:46:44 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_tilde(t_env *env, t_command *cmd_list)
{
	t_command	*cmd;
	t_token		*arg;

	cmd = cmd_list;
	while (cmd)
	{
		arg = cmd->arg_tokens;
		while (arg)
		{
			if (arg->quote_identifier == 0 && arg->content[0] == '~')
			{
				arg->content = replace_tilde(arg->content, env->env);
				if (!arg->content)
					return (1);
			}
			arg = arg->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

char	*replace_tilde(const char *content, char **env)
{
	char	*home;
	char	*result;
	size_t	result_len;

	if (!content || (content[0] != '~')
		|| (content[1] && content[1] != '/' && content[1] != '\0'))
		return (ft_strdup(content));
	home = find_var(env, "HOME");
	if (!home)
		return (ft_strdup(content));
	result_len = ft_strlen(home) + ft_strlen(content);
	result = malloc(result_len * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, home, result_len);
	ft_strlcat(result, content + 1, result_len);
	return (result);
}

int	expand_special(t_env *env, t_command *cmd_list)
{
	t_command	*cmd;
	t_token		*arg;
	char		*find;

	cmd = cmd_list;
	while (cmd)
	{
		arg = cmd_list->arg_tokens;
		while (arg)
		{
			find = ft_strchr(arg->content, '$');
			while (arg->quote_identifier != 1 && find != NULL
				&& (*(find + 1) == '?' || *(find + 1) == '-'))
			{
				arg->content = replace_special(arg->content,
						env->last_exit_status, find);
				if (!arg->content)
					return (1);
				find = ft_strchr(arg->content, '$');
			}
			arg = arg->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

char	*replace_special(char *content, int status, char *find)
{
	char	*special;
	int		new_len;

	if (*(find + 1) == '?')
	{
		special = ft_itoa(status);
		if (!special)
			return (NULL);
	}
	else if (*(find + 1) == '-')
	{
		special = ft_strdup("himBHs");
		if (!special)
			return (NULL);
	}
	else
		return (content);
	new_len = ft_strlen(content) - 2 + ft_strlen(special) + 1;
	return (create_special(new_len, special, content, find));
}

char	*create_special(int new_len, char *special, char *content, char *find)
{
	int		i;
	int		j;
	char	*result;

	result = malloc(new_len);
	if (!result)
		return (free (special), NULL);
	i = 0;
	while (content + i != find)
	{
		result[i] = content[i];
		i++;
	}
	j = 0;
	while (special[j])
		result[i++] = special[j++];
	j = (find - content) + 2;
	while (content[j])
		result[i++] = content[j++];
	result[i] = '\0';
	free(special);
	free(content);
	return (result);
}
