/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check_get_func.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:46:11 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/06 11:21:36 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wiexitstatus(int status)
{
	if ((status & 0xFF) == 0)
		return ((status >> 8) & 0xFF);
	return (-1);
}

// Custom getenv function
char	*ft_get(char *name, char **env)
{
	while (*env != NULL)
	{
		if (ft_strncmp(*env, name, ft_strlen(name)) == 0
			&& (*env)[ft_strlen(name)] == '=')
			return (*env + ft_strlen(name) + 1);
		env++;
	}
	return (NULL);
}
