/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quannguy <quannguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:47:02 by pbuchter          #+#    #+#             */
/*   Updated: 2025/02/04 13:14:15 by quannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer(char *input, t_token **head, t_env *env)
{
	int		i;

	i = 1;
	while (i)
	{
		if (token_construct(input, head))
		{
			clean_tokens(head);
			free(input);
			return (1);
		}
		i = check_tokens(&input, *head, env);
		if (i)
		{
			if (i == 2)
			{
				clean_tokens(head);
				free(input);
				return (1);
			}
		}
	}
	free(input);
	return (0);
}
