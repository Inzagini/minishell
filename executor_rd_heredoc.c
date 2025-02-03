#include "minishell.h"

static void	init(t_command *cmd_node, t_here_doc *doc);
static void	term(t_here_doc *doc);
static void	write_pipe(t_here_doc *doc, t_env *env);

int	here_doc_handle(t_command *cmd_node, t_env *env)
{
	t_here_doc	doc;

	init(cmd_node, &doc);
	while (doc.bytes_read)
	{
		write(1, "> ", 2);
		doc.bytes_read = read(0, doc.buffer, BUFFER_SIZE);
		if (doc.bytes_read == -1)
			break ;
		if (doc.bytes_read == 0)
		{
			write(2, "\n", 1);
			print_err(ft_get("SHELL", env->env),
				"warning: here-document delimited by end-of-file", NULL);
			break ;
		}
		doc.buffer[doc.bytes_read] = 0;
		if (ft_strncmp(doc.buffer, doc.delimiter, ft_strlen(doc.delimiter) + 1) == 10)
			break ;
		write_pipe(&doc, env);
	}
	term(&doc);
	return (doc.pipefd[0]);
}

static void	write_pipe(t_here_doc *doc, t_env *env)
{
	if (ft_strchr(doc->buffer, '$'))
	{
		doc->expanded = expand_argument(doc->buffer, env->env, doc->expanded);
		write(doc->pipefd[1], doc->expanded, ft_strlen(doc->expanded));
		free (doc->expanded);
	}
	else
		write(doc->pipefd[1], doc->buffer, doc->bytes_read);
}

static void	init(t_command *cmd_node, t_here_doc *doc)
{
	doc->bytes_read = 1;
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
