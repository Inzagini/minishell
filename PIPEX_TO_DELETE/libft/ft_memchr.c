/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:07:05 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:26:07 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//locates first occurance of c in s, within n bytes
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*src;

	i = 0;
	src = (const unsigned char *) s;
	while (i < n)
	{
		if ((unsigned char)src[i] == (unsigned char) c)
			return ((void *)&src[i]);
		i++;
	}
	return (NULL);
}
// #include <stdio.h>
// #include <assert.h>

// int main(void)
// {
//     char data[] = "Hello, world!";
//     size_t len = sizeof(data) - 1;
//     assert(ft_memchr(data, 'H', len) == &data[0]);
//     assert(ft_memchr(data, 'o', len) == &data[4]);
//     assert(ft_memchr(data, '!', len) == &data[12]);
//     assert(ft_memchr(data, 'x', len) == NULL);
//     assert(ft_memchr(data, 'w', 5) == NULL);
//     assert(ft_memchr(data, 'l', 3) == &data[2]);

//     printf("All tests passed!\n");
// 	return (0);
// }
