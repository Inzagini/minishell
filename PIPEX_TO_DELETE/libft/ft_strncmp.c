/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:50:14 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:27:11 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//compare two strings and return difference of first mismatch
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char	s1[6] = "ABCDE";
// 	char	s2[6] = "ABCDF";
// 	printf("%d", ft_strncmp(s1, s2, 12));
// 	return (0);
// }
