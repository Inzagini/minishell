/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:16:36 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:26:14 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//copies n specified character c from src to dst whithout any overwriting
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;
	size_t		i;

	if (n == 0 || dest == src)
		return (dest);
	s = (const char *)src;
	d = (char *)dest;
	i = -1;
	if (d < s)
		while (++i < n)
			d[i] = s[i];
	else if (d > s)
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (dest);
}
// #include <stdio.h>
// int main(void)
// {
//     char str[] = "Hello, World!";
//     ft_memmove(str, str + 7, 5); //moving "World" to the start of the string
//     printf("Result: %s\n", str);
//     return 0;
// }
