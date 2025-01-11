/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:36:11 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:26:10 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//compares byte by byte two memory locations until reached n, returs difference
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && str1[i] == str2[i])
		i++;
	if (i == n)
		return (0);
	return (str1[i] - str2[i]);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char	data[] = "Hello Xorld";
// 	char	data2[] = "Hello World";
// 	printf("%d\n", ft_memcmp(data, data2, 7));
// 	return (0);
// }
