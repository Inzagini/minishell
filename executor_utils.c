/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:19 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 11:43:20 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lst_len(t_command *lst)
{
	int			len;
	t_command	*head;

	len = 0;
	head = lst;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	lst = head;
	return (len);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	index;

	index = 0;
	if (!s1 || !s2)
	{
		return (1);
	}
	while (s1[index] == s2[index] && (s1[index] || s2[index]))
		index++;
	return (s1[index] - s2[index]);
}

void	print_err(char *prefix, char *msg, char *name)
{
	if (prefix)
	{
		write(2, prefix, ft_strlen(prefix));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (name)
	{
		write(2, ": ", 2);
		write(2, name, ft_strlen(name));
	}
	write(2, "\n", 1);
}

void	print_err_long(char *prefix, char *function, char *msg, char *attrib)
{
	if (prefix)
	{
		write(2, prefix, ft_strlen(prefix));
		write(2, ": ", 2);
	}
	write(2, function, ft_strlen(function));
	if (msg)
	{
		write(2, ": ", 2);
		write(2, msg, ft_strlen(msg));
	}
	if (attrib)
	{
		write(2, ": ", 2);
		write(2, attrib, ft_strlen(attrib));
	}
	write(2, "\n", 1);
}
