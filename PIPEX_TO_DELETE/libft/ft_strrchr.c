/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:43:09 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:51:17 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//find first occurance of c in s and return pointer to it
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	uc;
	char			*last_occurence;

	i = 0;
	uc = (unsigned char) c;
	last_occurence = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == uc)
			last_occurence = ((char *)(s + i));
		i++;
	}
	if (uc == '\0')
		return (((char *)(s + i)));
	return (last_occurence);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char *test = ft_strrchr("teste", 1024);
// 	printf("%p", &test);
// 	return (0);
// }
