/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:03:27 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:08:48 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//write character to spefified file descriptor
//(eg. standard output (1), standard error (2))
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
// int	main(void)
// {
// 	ft_putchar_fd('C', 2);
// 	ft_putchar_fd('\n', 2);
// 	return (0);
// }
