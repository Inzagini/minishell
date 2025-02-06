/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:42:04 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/06 14:37:37 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

extern volatile sig_atomic_t	g_sigint;

void	signal_setup(void);
void	heredoc_signal_handler(int sig);
void	disable_eof(void);
void	restore_terminal(void);

#endif
