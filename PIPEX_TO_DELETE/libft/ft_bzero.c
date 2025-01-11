/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:43:15 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:46:35 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//zeros n bytes of specified pointer s
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *) s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	char str[4] = {'A','B','C','D'} ;

	bzero(str, 3);
	printf("%s", str);
	printf("%s", str + 3);
	return (0);
}
*/
