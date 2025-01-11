/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:49:50 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:26:59 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//append src to the end of dst where size is the full space avail in dst
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	i;

	i = 0;
	dst_size = 0;
	src_size = 0;
	while (dst[dst_size] && dst_size < size)
		dst_size++;
	while (src[src_size])
		src_size++;
	if (size <= dst_size)
		return (size + src_size);
	while ((i < (size - dst_size -1)) && src[i])
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (dst_size + src_size);
}
// #include <stdio.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	char	*dest;
// 	char	src[] = "ABCD";

// 	dest = malloc(4);
// 	dest[0] = '\0';
// 	ft_strlcat(dest, src, 4);
// 	printf("%s\n", dest);
// 	free(dest);
// 	return (0);
// }
