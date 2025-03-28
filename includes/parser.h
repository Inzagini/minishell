/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:41:57 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/11 11:01:37 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//# include "minishell.h"

typedef struct s_command	t_command;
typedef struct s_env		t_env;

typedef struct s_command
{
	int			id;
	t_token		*arg_tokens;
	char		**args;
	int			*quotes;
	int			redir_in;
	int			redir_out;
	char		*redir_file_in;
	char		*redir_file_out;
	char		*heredoc_separator;
	int			size;
	int			builtin_flag;
	t_env		*env;
	t_command	*next;
}	t_command;

typedef struct s_parser
{
	t_command	*cmd_list;
	t_token		*token;
	t_command	*new_cmd;
	t_token		*arg_tokens;
	int			arg_group_id;
	int			size;
	int			id;
	int			redir_in;
	int			redir_out;
	char		*redir_file_in;
	char		*redir_file_out;
	char		*heredoc_sep;
	int			pipe_flag_in;
	int			pipe_flag_out;
	int			pipe_found;
	int			invalid_redirect_in;
	int			invalid_redirect_out;
	int			open_squote;
	int			open_dquote;
}	t_parser;

// parser.c
t_command	*parser(t_token *token_list, t_env *env);
void		initialize_parser(t_parser *parser, t_token *token_list);
void		reset_parser(t_parser *parser);
int			add_argument_token(t_parser *parser);

// parser_quotes.c
void		set_quote_identifier(t_token *new_token, t_token *current,
				t_parser *parser);
void		handle_quote_flag(t_parser *parser, t_token *token);

// parser_commands.c
int			cmdnew(t_parser *parser);
void		cmdadd(t_command **list, t_command *new);
void		handle_pipe_flags(t_parser *parser);
int			handle_pipes(t_parser *parser);
void		update_arg_id_deltas(t_token *input);

// parser_redirects_quotes.c
int			handle_redirects(t_parser *parser, t_env *env);
int			set_redirects_single(t_parser *parser, t_token_type type);
int			set_redirect_in(t_parser *parser);
int			set_redirect_out(t_parser *parser);

// parser_redirects_double
int			set_redirects_double(t_parser *parser, t_token_type type);
int			set_redirect_append(t_parser *parser);

// parser_cleaner.c
void		clean_parser(t_parser *parser);
void		clean_commands(t_command *cmd_list);
void		clean_cmd_list(t_command **cmd_list);

#endif
