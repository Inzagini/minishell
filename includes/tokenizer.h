#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef struct s_token_structure	t_token;

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

//token handle
t_token	*tokenizer(char *input_str, t_token **head);
t_token	*create_token(char *content, t_token_type token_type);
void	append_token_lst(t_token **head, t_token *new_token);
int		sep_handle(char *str, int *index, t_token **head);
int		pipe_handle(char *str, int *index, t_token **head);
int		squote_handle(char *str, int *index, t_token **head);
int	arg_handle(char *input_str, int start, int index, t_token **head);
int	cmd_handle(char *input_str, int start, int index, t_token **head);
#endif
