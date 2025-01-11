/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:43:15 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:26:16 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//writes n specified character c to specified memory location s)
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *) s;
	while (i < n)
	{
		ptr[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char str[4] = {'A','B','C', '\0'} ;

// 	ft_memset(str, 78, 2); //overwriting the first two bytes with a 'N'
// 	printf("%s\n", str);
// 	return (0);
// }
