/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:34:57 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:27:02 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//copies up to size-1 characters from src to dst
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	source_size;

	i = 0;
	source_size = 0;
	while (src[source_size] != '\0')
	{
		source_size++;
	}
	if (size == 0)
		return (source_size);
	while (i < (size -1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (source_size);
}
// #include <stdio.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	char	*dest;
// 	char	src[] = "ABCD";

// 	dest = malloc(4);
// 	dest[0] = '\0';
// 	ft_strlcpy(dest, src, 4);
// 	printf("%s\n", dest);
// 	free(dest);
// 	return (0);
// }
