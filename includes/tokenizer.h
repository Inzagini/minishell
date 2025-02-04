/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:42:13 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:42:14 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef struct s_env				t_env;
typedef struct s_token_structure	t_token;

typedef enum e_token_types
{
	CMD,
	ARG,
	PIPE,
	RD_OUT,
	RD_IN,
	RD_APP,
	RD_HEREDOC,
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
	char			*content;
	t_token			*previous;
	t_token			*next;
	int				quote_identifier;
	int				arg_group_id;
	int				arg_group_id_delta;
}	t_token;

typedef struct s_token_data
{
	int	index;
	int	start;
	int	cmd_flag;
	int	rd_flag;
	int	pipe_flag;
	int	exit_flag;
}	t_data;

//token handle
int		tokenizer(char *input, t_token **head, t_env *env);
int		token_construct(char *input_str, t_token **head);
t_token	*create_token(char *content, t_token_type token_type);
void	append_token_lst(t_token **head, t_token *new_token);
int		token_quotes(t_token **head, t_data *data, t_token_type type);

int		cmd_handle(char *input_str, t_data *data, t_token **head);
int		arg_handle(char *input_str, t_data *data, t_token **head);
int		sep_handle(char *input_str, t_data *data, t_token **head);
int		pipe_handle(t_data *data, t_token **head);

int		rd_handle(char *input_str, t_data *data, t_token **head);
int		rd_out_handle(char *input_str, t_data *data, t_token **head);
int		rd_in_handle(char *input_str, t_data *data, t_token **head);
int		rd_app_handle(char *input_str, t_data *data, t_token **head);
int		rd_heredoc_handle(char *input_str, t_data *data, t_token **head);

int		squote_handle(char *input_str, t_data *data, t_token **head);
int		dquote_handle(char *input_str, t_data *data, t_token **head);
int		new_line_handle(char *input_str, t_data *data, t_token **head);

int		check_tokens(char **input, t_token *token_lst, t_env *env);
void	clean_tokens(t_token **head);
void	print_tokens(t_token *token_list);

#endif
