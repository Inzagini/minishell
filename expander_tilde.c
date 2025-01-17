#include "minishell.h"

int	expand_tilde(t_env *env, t_command *cmd_list)
{
	t_command	*cmd;
	t_token		*arg;

	cmd = cmd_list;
	while (cmd)
	{
		arg = cmd_list->arg_tokens;
		while (arg)
		{
			if (arg->quote_identifier == 0 && arg->content[0] == '~')
			{
				arg->content = replace_tilde(arg->content, env->env_current);
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

int	expand_question(t_env *env, t_command *cmd_list)
{
	t_command	*cmd;
	t_token		*arg;

	cmd = cmd_list;
	while (cmd)
	{
		arg = cmd_list->arg_tokens;
		while (arg)
		{
			if (arg->quote_identifier != 1 && arg->content[0] == '$' && arg->content[1] == '?')
			{
				arg->content = replace_question(arg->content, env->last_exit_status);
				if (!arg->content)
					return (1);
			}
			arg = arg->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

char	*replace_question(char *content, int status)
{
	char	*question;
	char	*result;

	question = ft_itoa(status);
	if (!question)
		return (NULL);
	result = ft_strjoin(question, content + 2);
	free (question);
	free (content);
	return (result);
}
