/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:34:14 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:09:33 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//allocate and copy substring from s starting at start of len characters
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
	{
		result = malloc(1);
		if (result)
			result[0] = '\0';
		return (result);
	}
	if (start + len > str_len)
		len = str_len - start;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len && s[start + i])
		result[i] = s[start + i];
	result[i] = '\0';
	return (result);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char	*substr;
// 	substr = ft_substr("", 0, 5);
// 	printf("%s\n", substr);
// 	free(substr);
// 	substr = ft_substr("hello", 10, 5);
// 	printf("%s\n", substr);
// 	free(substr);
// 	substr = ft_substr("hello", 2, 10);
// 	printf("%s\n", substr);
// 	free(substr);
// 	return (0);
// }
