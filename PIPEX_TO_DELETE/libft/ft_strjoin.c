/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:13:20 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:09:16 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//creates memory to join two strings, outputs pointer to joined string
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	length1;
	size_t	length2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	length1 = ft_strlen(s1);
	length2 = ft_strlen(s2);
	result = malloc((length1 + length2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < length1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < length1 + length2)
	{
		result[i] = s2[i - length1];
		i++;
	}
	result[i] = '\0';
	return (result);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char *strjoined;
// 	strjoined = ft_strjoin("ABCD", "abc");
// 	printf("%s\n", strjoined);
// 	free(strjoined);
// 	return(0);
// }
