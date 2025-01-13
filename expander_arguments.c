// #include "minishell.h"

// // if the VAR cannot be found, it expands to 0
// // can rely on the identified quotes
// // if in double quotes -> expands into single argument (no word splitting)
// // if in single quotes -> expands into multiple arguments (word splitting)

// int	is_valid_var_char(char c)
// {
// 	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
// 		|| (c >= '0' && c <= '9'));
// }

// char	*find_var(char **env, char *var)
// {
// 	int	len;
// 	int	i;

// 	len = ft_strlen(var);
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
// 			return (&env[i][len + 1]);
// 		i++;
// 	}
// 	return ("");
// }

// char	*append_to_result(char *result, char *to_add, size_t *len)
// {
// 	char	*temp;
// 	size_t	add_len;
// 	size_t	total_len;

// 	add_len = ft_strlen(to_add);
// 	total_len = *len + add_len;
// 	temp = result;
// 	result = malloc(total_len + 1);
// 	if (!result)
// 	{
// 		free(temp);
// 		return (NULL);
// 	}
// 	ft_strlcpy(result, temp, total_len + 1);
// 	ft_strlcat(result, to_add, total_len + 1);
// 	*len += add_len;
// 	free(temp);
// 	return (result);
// }

// char	*expand_argument(char *arg, char **env)
// {
// 	char	*result;
// 	char	*start;
// 	char	*dollar;
// 	size_t	len;

// 	start = arg;
// 	result = malloc(1);
// 	if (!result)
// 		return (NULL);
// 	result[0] = '\0';
// 	len = 0;
//     dollar = ft_strchr(start, '$');
// 	while ((dollar = ft_strchr(start, '$')))
// 	{
// 		result = append_to_result(result, ft_strndup(start, dollar - start), &len);
// 		if (!result)
// 			return (NULL);
// 		start = dollar + 1;
// 		result = append_to_result(result, find_var(env, ft_strndup(start,
// 		ft_strspn(start, "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"))), &len);
// 		if (!result)
// 			return (NULL);
// 		start += ft_strspn(start, "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
//         dollar = ft_strchr(start, '$');
// 	}
// 	result = append_to_result(result, start, &len);
// 	return (result);
// }

// int	expand_arguments(t_env *env, t_command *cmd_list)
// {
// 	char	*expanded;
// 	int		i;

// 	while (cmd_list)
// 	{
// 		i = 0;
// 		while (cmd_list->arguments[i])
// 		{
// 			if (cmd_list->quote_identifier[i] != 1)
//             {
//                 expanded = expand_argument(cmd_list->arguments[i], env->env_current);
//                 if (!expanded)
//                     return (1);
//                 free(cmd_list->arguments[i]);
//                 cmd_list->arguments[i] = expanded;
//             }
//             i++;
// 		}
// 		cmd_list = cmd_list->next;
// 	}
// 	return (0);
// }

// char	*ft_strndup(const char *src, size_t n)
// {
// 	char	*dup;
// 	size_t	i;

// 	dup = malloc(n + 1);
// 	if (!dup)
// 		return (NULL);
// 	i = 0;
// 	while (i < n)
// 	{
// 		dup[i] = src[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }

// size_t	ft_strspn(const char *str, const char *accept)
// {
// 	size_t	i;
// 	size_t	j;
// 	int		found;

// 	i = 0;
// 	while (str[i])
// 	{
// 		j = 0;
// 		found = 0;
// 		while (accept[j])
// 		{
// 			if (str[i] == accept[j])
// 			{
// 				found = 1;
// 				break ;
// 			}
// 			j++;
// 		}
// 		if (!found)
// 			break ;
// 		i++;
// 	}
// 	return (i);
// }
