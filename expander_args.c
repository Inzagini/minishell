#include "minishell.h"

char	*expand_argument(char *arg, char **env, char *result)
{
	char	*start;
	char	*var_pos;
	char	*to_add;
	size_t	len;

	start = arg;
	result = ft_strdup("");
	len = 0;
	var_pos = ft_strchr(start, '$');
	while (var_pos)
	{
		to_add = ft_strndup(start, var_pos - start);
		result = append(result, to_add, &len);
		if (!result)
			return (free(to_add), NULL);
		free (to_add);
		start = var_pos + 1;
		to_add = ft_strndup(start, ft_strspn(start));
		result = append(result, find_var(env, to_add), &len);
		free (to_add);
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
	temp = malloc(total_len + 1);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	ft_strlcpy(temp, result, total_len + 1);
	ft_strlcat(temp, to_add, total_len + 1);
	*len += add_len;
	free(result);
	return (temp);
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
						env->env, expanded);
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
