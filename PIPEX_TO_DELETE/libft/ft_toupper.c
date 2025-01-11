/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:21:27 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:09:47 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 'a' + 'A';
	return (c);
}
// #include <unistd.h>
// int	main(void)
// {
// 	char c = ft_toupper('n');
// 	write(1, &c, 1);
// 	return (0);
// }
