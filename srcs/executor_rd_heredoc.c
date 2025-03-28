/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_rd_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:13 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/11 11:05:34 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(t_command *cmd_node, t_here_doc *doc);
static void	term(t_here_doc *doc, t_exdat *data);
static int	write_pipe(t_here_doc *doc, t_env *env);
static int	check_delim(t_here_doc *doc);

int	here_doc_handle(t_command *cmd_node, t_env *env, t_exdat *data)
{
	t_here_doc	doc;

	init(cmd_node, &doc);
	while (1)
	{
		doc.line = readline("> ");
		if (g_sigint)
			term(&doc, data);
		if (!doc.line)
			print_err(ft_get("SHELL", env->env), HEREDOC_WARNING, NULL);
		if (doc.line[0] == '\0')
		{
			free(doc.line);
			continue ;
		}
		if (check_delim(&doc) == 0)
		{
			free(doc.line);
			break ;
		}
		if (write_pipe(&doc, env) == -1)
			break ;
	}
	return (term(&doc, data), doc.pipefd[0]);
}

static int	check_delim(t_here_doc *doc)
{
	int	check;

	check = ft_strncmp(doc->line, doc->delimiter,
			ft_strlen(doc->delimiter) + 1);
	return (check);
}

static int	write_pipe(t_here_doc *doc, t_env *env)
{
	char	*tmp;

	tmp = doc->line;
	doc->line = ft_strjoin(doc->line, "\n");
	free(tmp);
	if (!doc->line)
	{
		doc->error = -1;
		perror("Here doc malloc:");
		return (-1);
	}
	if (ft_strchr(doc->line, '$'))
	{
		doc->expanded = expand_argument(doc->line, env->env, doc->expanded);
		write(doc->pipefd[1], doc->expanded, ft_strlen(doc->expanded));
		free (doc->expanded);
	}
	else
		write(doc->pipefd[1], doc->line, ft_strlen(doc->line));
	free(doc->line);
	return (0);
}

static void	init(t_command *cmd_node, t_here_doc *doc)
{
	doc->line = NULL;
	doc->delimiter = cmd_node->heredoc_separator;
	doc->error = 0;
	if (pipe(doc->pipefd) == -1)
	{
		perror ("BrokenPipeError:");
		exit (32);
	}
	doc->sa_new.sa_handler = heredoc_signal_handler;
	doc->sa_new.sa_flags = 0;
	sigemptyset(&doc->sa_new.sa_mask);
	sigaction(SIGINT, &doc->sa_new, &doc->sa_old);
}

static void	term(t_here_doc *doc, t_exdat *data)
{
	close(doc->pipefd[1]);
	sigaction(SIGINT, &doc->sa_old, NULL);
	if (doc->error == -1)
	{
		close(doc->pipefd[0]);
		exit (EXIT_FAILURE);
	}
	if (g_sigint)
	{
		close_all_pipes(data->pipefd);
		close(doc->pipefd[0]);
		g_sigint = 0;
		exit(130);
	}
}
