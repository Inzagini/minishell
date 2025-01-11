/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:09:49 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:09:07 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// copy a string to a newly allocated memory function
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	result = malloc((i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
// #include <stdio.h>

// int	main(void)
// {
// 	char	str[] = "ABCDE";
// 	char	*result;

// 	result = ft_strdup(str);
// 	printf("%s", result);
// 	free(result);
// 	return (0);
// }
