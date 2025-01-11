/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:49:12 by paulbuchter       #+#    #+#             */
/*   Updated: 2024/12/09 10:39:16 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *input, ...)
{
	va_list	ap;
	int		pos;
	int		count;
	int		write_return;

	va_start(ap, input);
	pos = 0;
	count = 0;
	while (input[pos])
	{
		if (input[pos] == '%')
		{
			write_return = ft_printf_helper(&pos, &ap, input);
			if (write_return == -1)
				return (va_end(ap), -1);
			count += write_return;
			pos += 2;
		}
		else if (write(1, &input[pos++], 1) == -1)
			return (va_end(ap), -1);
		else
			count++;
	}
	va_end(ap);
	return (count);
}
