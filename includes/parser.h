#include "minishell.h"

typedef struct s_command	t_command;

typedef struct s_command   //malloc
{
	int			id;
	char		*name;
	char		**arguments;  //malloc (name is element of argument array, so no need to free separately)
	int			quote_identifier[100];
	int			redir_in;
	int			redir_out;
	char		*redir_file_in;  //malloc
	char		*redir_file_out; //malloc
	int			size;
	t_command	*next;
}	t_command;

typedef struct s_parser		// no need to free (no dynamic allocation)
{
	t_command	*cmd_list;
	t_token		*curr_token;
	t_command	*new_cmd;
	char		**args;		// no need to free as handed over to command (unless it fails before handing over to command)
	int			size;
	int			id;
	int			redir_in;
	int			redir_out;
	char		*redir_file_in;	// no need to free as handed over to command (unless it fails before handing over to command)
	char		*redir_file_out; // no need to free as handed over to command (unless it fails before handing over to command)
	int			double_quotes;
	int			single_quotes;
	int			quote_identifier[100];
}	t_parser;

// parser.c functions

t_command	*parser(t_token *token_list);
int			cmdnew(t_parser *parser);
void		cmdadd_back(t_command **list, t_command *new);
char		**add_argument(t_parser *parser);
int			handle_redirects(t_parser *parser);
int			handle_quotes(t_token *curr_token, t_parser *parser);
void		initialize_parser(t_parser *parser, t_token *token_list);
void		reset_parser(t_parser *parser);

// parser_cleaning.c functions

void		clean_parser(t_parser *parser);
void		clean_commands(t_command *cmd_list);
void		clean_cmd_list(t_command **cmd_list);

// test functions only. delete later
void print_command(t_command *cmd);
void free_tokens(t_token *token_list);
