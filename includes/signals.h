/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:42:04 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:42:10 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

extern volatile sig_atomic_t	g_heredoc_interrupted;

void	signal_setup(void);
void	heredoc_signal_handler(int sig);
void	disable_eof(void);
void	restore_terminal(void);

#endif
