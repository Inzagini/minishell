#include "minishell.h"

#ifndef PARSER_H
# define PARSER_H


typedef struct s_command	t_command;
typedef struct s_env		t_env;

typedef struct s_command   //malloc
{
	int			id;
	t_token		*arg_tokens;  //malloc
	char		**args;
	int			redir_in;
	int			redir_out;
	char		*redir_file_in;  //malloc
	char		*redir_file_out; //malloc
	char		*heredoc_separator; //malloc
	int			size;
	int			builtin_flag;
	t_env		*env;
	t_command	*next;
}	t_command;

typedef struct s_parser		// no need to free (no dynamic allocation)
{
	t_command	*cmd_list;
	t_token		*token;
	t_command	*new_cmd;
	t_token		*arg_tokens; //malloc
	int			arg_group_id;
	int			size;
	int			id;
	int			redir_in;	// 0 no redirection || 1 redirect to file || 2 heredoc || 3 redirect to pipe
	int			redir_out;	// 0 no redirection || 1 redirect to file || 2 redirect to file *append || 3 redirect to pipe
	char		*redir_file_in;	// no need to free as handed over to command (unless it fails before handing over to command)
	char		*redir_file_out; // no need to free as handed over to command (unless it fails before handing over to command)
	char		*heredoc_separator; // no need to free as handed over to command (unless it fails before handing over to command)
	int			pipe_flag_in;
	int			pipe_flag_out;
	int			pipe_found;
}	t_parser;

// parser.c functions
t_command	*parser(t_token *token_list);
int			cmdnew(t_parser *parser);
void		cmdadd(t_command **list, t_command *new);
int			add_argument_token(t_parser *parser);
void		set_quote_identifier(t_token *new_token, t_token *current);
int			handle_redirects(t_parser *parser);
int			handle_pipes (t_parser *parser);
void		handle_pipe_flags(t_parser *parser);
int			set_redirects_single(t_parser *parser, t_token_type type);
int			set_redirects_double(t_parser *parser, t_token_type type);


void		initialize_parser(t_parser *parser, t_token *token_list);
void		reset_parser(t_parser *parser);

// parser_cleaning.c functions

void		clean_parser(t_parser *parser);
void		clean_commands(t_command *cmd_list);
void		clean_cmd_list(t_command **cmd_list);

// test functions only. delete later
void print_command(t_command *cmd);
void free_tokens(t_token *token_list);

#endif
