/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:24:37 by quannguy          #+#    #+#             */
/*   Updated: 2025/01/08 11:33:13 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>

# define PIPE
# define IN_FILE
# define OUT_FILE

typedef struct s_token_structure
{
	int		type;
	char	*content;
	t_token	*previous;
	t_token	*next;
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
