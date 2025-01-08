/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:36:13 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:27:05 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//returns length of string
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
// #include <stdio.h>
// int	main(void)
// {
// 	printf("%zu\n", ft_strlen("ABCDEF"));
// 	return (0);
// }
