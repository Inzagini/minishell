/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:08:23 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:08:13 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
// #include <stdio.h>
// int	main(void)
// {
// 	printf("a: %d\n", ft_isdigit('a'));
// 	printf("7: %d\n", ft_isdigit('7'));
// 	return (0);
// }
