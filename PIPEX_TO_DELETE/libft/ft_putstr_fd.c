/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:14:34 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:08:59 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//write string to spefified file descriptor
//(eg. standard output (1), standard error (2))
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
// int	main(void)
// {
// 	ft_putstr_fd("ABCDEF", 2);
// 	return (0);
// }
