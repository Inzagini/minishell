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

typedef struct s_token_data
{
	int	index;
	int	start;
	int	cmd_flag;
	int	rd_flag;
	int	exit_flag;
}	t_data;


//token handle
int	tokenizer(char *input_str, t_token **head);

t_token	*create_token(char *content, t_token_type token_type);
void	append_token_lst(t_token **head, t_token *new_token);

int		cmd_handle(char *input_str, t_data *data, t_token **head);
int		arg_handle(char *input_str, t_data *data, t_token **head);
int		sep_handle(char *input_str, t_data *data, t_token **head);
int		pipe_handle(char *input_str, t_data *data, t_token **head);

int		rd_handle(char *input_str, t_data *data, t_token **head);
int		rd_out_handle(char *input_str, t_data *data, t_token **head);
int		rd_in_handle(char *input_str, t_data *data, t_token **head);
int		rd_app_handle(char *input_str, t_data *data, t_token **head);
int		rd_inin_handle(char *input_str, t_data *data, t_token **head);

int		squote_handle(char *input_str, t_data *data, t_token **head);
int		dquote_handle(char *input_str, t_data *data, t_token **head);
int		new_line_handle (t_data *data, t_token **head);

void	token_cleaner(t_token *head);
#endif
