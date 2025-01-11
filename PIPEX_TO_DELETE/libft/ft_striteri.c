/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:20:08 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:09:11 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// applies function to each element of string s
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
// #include <stdio.h>
// void to_uppercase(unsigned int index, char *c)
// {
//     (void)index;
// 	if (*c >= 'a' && *c <= 'z')
//         *c = *c - 32;
// }

// int main(void)
// {
//     char str[] = "hello world";

//     ft_striteri(str, to_uppercase);
//     printf("%s\n", str);
//     return 0;
// }
