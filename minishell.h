/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:24:37 by quannguy          #+#    #+#             */
/*   Updated: 2025/01/08 11:39:17 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

//define type of the tokens
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
	SQUOTE,
	DQUOTE,
	LPAREN,
	RPAREN,
	ENV_VAR,
	NEW_LINE,
	INVAL
}	t_token_type;

typedef struct s_token_structure
{
	t_token_type	type;
	char			*content;
	t_token			*previous;
	t_token			*next;
}	t_token;


typedef struct s_command
{
	char		*name;
	char		**arguments;
	t_command	*next;
	int			*redir_in;
	int			*redir_out;
	char		*redir_file;
}	t_command;


#endif
