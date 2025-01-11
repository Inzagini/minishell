/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:07:27 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:26:12 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//copies n bytes from src to dst without handling potential overlaps
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	const char	*s;
	char		*d;

	i = 0;
	s = (const char *) src;
	d = (char *) dst;
	if ((dst == NULL && src == NULL) && n > 0)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	const char	src[] = "ABCD";
// 	char 		dest[3];
// 	ft_memcpy

// 	memcpy(((void *)0), ((void *)0), 3);
// 	ft_memcpy(dest, src, 2);
// 	dest[2] = '\0';
// 	printf("%s\n", dest);
// 	return (0);
// }
