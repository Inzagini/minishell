#include "minishell.h"

typedef struct s_command	t_command;

typedef struct s_command   //malloc
{
	int			id;
	char		*name;
	char		**arguments;  //malloc (name is element of argument array, so no need to free separately)
	int			redir_in;
	int			redir_out;
	char		*redir_file_in;  //malloc
	char		*redir_file_out; //malloc
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
	char		*redir_file_in;
	char		*redir_file_out;
}	t_parser;

// parser.c functions

t_command	*parser(t_token *token_list);
t_command	*cmdnew(t_parser *parser);
void		cmdadd_back(t_command **list, t_command *new);
char		**add_argument(char **args, int *size, const char *arg);
void		initialize_parser(t_parser *parser);
void		reset_parser(t_parser *parser);

// test functions only. delete later
void print_command(t_command *cmd);
void free_tokens(t_token *token_list);
void free_commands(t_command *cmd_list);
