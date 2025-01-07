/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:24:37 by quannguy          #+#    #+#             */
/*   Updated: 2025/01/07 15:40:56 by quannguy         ###   ########.fr       */
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

#endif
