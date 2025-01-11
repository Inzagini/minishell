/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:31:07 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:26:40 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// find first occurence of character in string, return pointer to that occurence
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	i = 0;
	uc = (unsigned char) c;
	if (uc == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (s[i])
	{
		if (s[i] == uc)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	return (0);
}
// #include <stdio.h>
// int main()
// {
// 	const char str[] = "Hello, world!";
// 	char c = 'o';
//  char *result = ft_strchr("teste", 1024);
//  printf("%p", &result);
//  return (0);
// 	printf("First occurrence of '%c' is at index: %ld\n", c, result - str);
//strchr returns pointer to first occurence.
//  }
