/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:02:02 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:09:23 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//apply function to every character of s and store in new, allocated string
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	result = malloc((i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
// char ft_toupper1(unsigned int index, char c)
// {
//     (void)index;
//     if (c >= 'a' && c <= 'z')
//         return (c - 'a' + 'A');
//     return (c);
// }

// #include <stdio.h>

// int main(void)
// {
//     char *result = ft_strmapi("hello worLD", ft_toupper1);

//     if (result)
//     {
//         printf("%s\n", result);
//         free(result);
//     }
//     return (0);
// }
