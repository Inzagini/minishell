
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

//define type of the tokens
typedef struct s_token_structure	t_token;
typedef struct s_command			t_command;

typedef enum e_token_types
{
	CMD,
	ARG,
	PIPE,
	RD_OUT,
	RD_IN,
	RD_APP,
	RD_ININ,
	SEP,
	SQUOTE,
	DQUOTE,
	LPAREN,
	RPAREN,
	ENV_VAR,
	NEW_LINE,
	INVAL,
}	t_token_type;

typedef struct s_token_structure
{
	t_token_type	type;
	char			*content;	//malloc
	t_token			*previous;	//malloc
	t_token			*next;		//malloc
}	t_token;

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

t_token	*create_token(char *content, t_token_type token_type);
void	append_token_lst(t_token **head, t_token *new_token);
int		sep_handle(char *str, int index, t_token **head);
int		pipe_handle(char *str, int index, t_token **head);
int	squote_handle(char *str, int index, t_token **head);





//token handle
t_token	*create_token(char *content, t_token_type token_type);
void	append_token_lst(t_token **head, t_token *new_token);
int		sep_handle(char *str, int index, t_token **head);
int		pipe_handle(char *str, int index, t_token **head);
int	squote_handle(char *str, int index, t_token **head);
#endif
