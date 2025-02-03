#include "minishell.h"

static void	init(t_command *cmd_node, t_here_doc *doc);
static void	term(t_here_doc *doc);
static void	write_pipe(t_here_doc *doc, t_env *env);

int	here_doc_handle(t_command *cmd_node, t_env *env)
{
	t_here_doc	doc;

	init(cmd_node, &doc);
	while (1)
	{
		doc.line = readline("> ");
		if (!doc.line)
		{
			print_err(ft_get("SHELL", env->env),
				"warning: here-document delimited by end-of-file", NULL);
			break ;
		}
		if (doc.line[0] == '\0')
		{
			free(doc.line);
			break ;
		}
		if (ft_strncmp(doc.line, doc.delimiter,
				ft_strlen(doc.delimiter) + 1) == 0)
			break ;
		write_pipe(&doc, env);
	}
	term(&doc);
	return (doc.pipefd[0]);
}

static void	write_pipe(t_here_doc *doc, t_env *env)
{
	char	*tmp;

	tmp = doc->line;
	doc->line = ft_strjoin(doc->line, "\n");
	free(tmp);
	if (ft_strchr(doc->line, '$'))
	{
		doc->expanded = expand_argument(doc->line, env->env, doc->expanded);
		write(doc->pipefd[1], doc->expanded, ft_strlen(doc->expanded));
		free (doc->expanded);
	}
	else
		write(doc->pipefd[1], doc->line, ft_strlen(doc->line));
}

static void	init(t_command *cmd_node, t_here_doc *doc)
{
	doc->line = NULL;
	doc->delimiter = cmd_node->heredoc_separator;
	pipe(doc->pipefd);
	doc->sa_new.sa_handler = heredoc_signal_handler;
	doc->sa_new.sa_flags = 0;
	sigemptyset(&doc->sa_new.sa_mask);
	sigaction(SIGINT, &doc->sa_new, &doc->sa_old);
	disable_eof();
}

static void	term(t_here_doc *doc)
{
	close(doc->pipefd[1]);
	sigaction(SIGINT, &doc->sa_old, NULL);
	restore_terminal();
	if (g_heredoc_interrupted)
	{
		close(doc->pipefd[0]);
		exit(130);
	}
}
