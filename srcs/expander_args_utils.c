/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_args_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:43:30 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/07 16:15:39 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c)
{
	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strspn(const char *str)
{
	size_t	i;
	size_t	j;
	int		found;
	char	*ok;

	ok = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	i = 0;
	while (str[i])
	{
		j = 0;
		found = 0;
		while (ok[j])
		{
			if (str[i] == ok[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (!found)
			break ;
		i++;
	}
	return (i);
}

void	free_split(char **split_tokens)
{
	int	i;

	if (!split_tokens)
		return ;
	i = 0;
	while (split_tokens[i])
	{
		free(split_tokens[i]);
		i++;
	}
	free(split_tokens);
}
