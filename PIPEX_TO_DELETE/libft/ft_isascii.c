/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:31:11 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:08:10 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
// #include <stdio.h>
// int	main(void)
// {
// 	printf("a: %d\n", ft_isascii('a'));
// 	printf("128: %d\n", ft_isascii(128));
// 	return (0);
// }
