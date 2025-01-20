#include "minishell.h"

char	*expand_argument(char *arg, char **env, char *result)
{
	char	*start;
	char	*var_pos;
	size_t	len;

	start = arg;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	len = 0;
	var_pos = ft_strchr(start, '$');
	while (var_pos)
	{
		result = append(result, ft_strndup(start, var_pos - start), &len);
		if (!result)
			return (NULL);
		start = var_pos + 1;
		result = append(result, find_var(env,
					ft_strndup(start, ft_strspn(start))), &len);
		if (!result)
			return (NULL);
		start += ft_strspn(start);
		var_pos = ft_strchr(start, '$');
	}
	result = append(result, start, &len);
	return (result);
}

char	*append(char *result, char *to_add, size_t *len)
{
	char	*temp;
	size_t	add_len;
	size_t	total_len;

	add_len = ft_strlen(to_add);
	total_len = *len + add_len;
	temp = result;
	result = malloc(total_len + 1);
	if (!result)
	{
		free(temp);
		return (NULL);
	}
	ft_strlcpy(result, temp, total_len + 1);
	ft_strlcat(result, to_add, total_len + 1);
	*len += add_len;
	free(temp);
	return (result);
}

int	expand_arguments_dquote(t_env *env, t_command *cmd_list)
{
	char	*expanded;
	t_token	*arg;

	expanded = NULL;
	while (cmd_list)
	{
		arg = cmd_list->arg_tokens;
		while (arg)
		{
			if (arg->quote_identifier == 2)
			{
				expanded = expand_argument(arg->content,
						env->env_current, expanded);
				if (!expanded)
					return (1);
				free(arg->content);
				arg->content = expanded;
			}
			arg = arg->next;
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}

char	*find_var(char **env, char *var)
{
	int	len;
	int	i;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	if (len > 0)
		return ("");
	return ("$");
}
