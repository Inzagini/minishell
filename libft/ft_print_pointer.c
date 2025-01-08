/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:40:22 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/01 11:27:20 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_pointer(va_list *ap)
{
	void			*ptr;
	unsigned long	address;

	ptr = va_arg(*ap, void *);
	if (!ptr)
	{
		if (write(1, "(nil)", 5) == (-1))
			return (-1);
		return (5);
	}
	address = (unsigned long)ptr;
	if (write(1, "0x", 2) == -1)
		return (-1);
	else
		return (ft_putnbr_base(address, "0123456789abcdef") + 2);
}
