/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:59:29 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:30:37 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//find needle in haystack within len first characters of haystack
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;
	size_t	j;

	i = -1;
	little_len = 0;
	if (big == NULL || little == NULL)
		i = big[0];
	if (*little == '\0')
		return ((char *)big);
	while (little[little_len])
		little_len++;
	if (little_len > len)
		return (NULL);
	while (++i < (len - little_len + 1) && big[i])
	{
		j = 0;
		while (big[i + j] == little[j])
		{
			j++;
			if (j == little_len)
				return ((char *)&big[i]);
		}
	}
	return (NULL);
}
// #include <stdio.h>
// int main(void)
// {
// 	char *big = NULL;
// 	// char little[] = "abcd";
		// printf("%p", ft_strnstr(big, "", 0));
// // 	printf("%s", ft_strnstr(big, little, 9));
// 	return (0);
// }
