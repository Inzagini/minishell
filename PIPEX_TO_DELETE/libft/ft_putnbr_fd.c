/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:31:47 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 18:26:28 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//write int to spefified file descriptor
//(eg. standard output (1), standard error (2))
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = (long) n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = (-nbr);
	}
	if (nbr >= 10)
		ft_putnbr_fd((nbr / 10), fd);
	ft_putchar_fd((nbr % 10 + '0'), fd);
}
// #include <limits.h>
// int	main(void)
// {
// 	ft_putnbr_fd(INT_MIN, 2);
// 	return (0);
// }
