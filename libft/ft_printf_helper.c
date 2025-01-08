/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:09:39 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/01 11:27:31 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_helper(int *i, va_list *ap, const char *input)
{
	int	count;

	if (input[*i + 1] == 'd' || input[*i + 1] == 'i')
		count = ft_print_int(ap);
	else if (input[*i + 1] == 'c')
		count = ft_print_c(ap);
	else if (input[*i + 1] == 'u')
		count = ft_print_uint(ap);
	else if (input[*i + 1] == 's')
		count = ft_print_string(ap);
	else if (input[*i + 1] == '%')
		count = ft_print_percent();
	else if (input[*i + 1] == 'x')
		count = ft_print_hex_lower(ap);
	else if (input[*i + 1] == 'X')
		count = ft_print_hex_upper(ap);
	else if (input[*i + 1] == 'p')
		count = ft_print_pointer(ap);
	else
	{
		ft_putchar_fd('%', 1);
		ft_putchar_fd(input[*i + 1], 1);
		return (2);
	}
	return (count);
}
