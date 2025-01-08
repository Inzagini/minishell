/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:19:55 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:08:52 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//write "string\n" to spefified file descriptor
//(eg. standard output (1), standard error (2))
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
// int	main(void)
// {
// 	ft_putendl_fd("ABCDEF", 2);
// 	return (0);
// }
