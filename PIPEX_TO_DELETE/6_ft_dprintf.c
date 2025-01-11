/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_ft_dprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:31:22 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/18 10:04:15 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_dprint_string(va_list *ap)
{
	char	*output;
	int		i;

	i = 0;
	output = va_arg(*ap, char *);
	if (!output)
		output = "(null)";
	while (output[i])
	{
		if (write(2, &output[i], 1) == (-1))
			return (-1);
		i++;
	}
	return (ft_strlen(output));
}

int	ft_dprintf_helper(int *i, va_list *ap, const char *input)
{
	int	count;

	if (input[*i + 1] == 's')
		count = ft_dprint_string(ap);
	else
	{
		ft_putchar_fd('%', 2);
		ft_putchar_fd(input[*i + 1], 2);
		return (2);
	}
	return (count);
}

int	ft_dprintf(const char *input, ...)
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
			write_return = ft_dprintf_helper(&pos, &ap, input);
			if (write_return == -1)
				return (va_end(ap), -1);
			count += write_return;
			pos += 2;
		}
		else if (write(2, &input[pos++], 1) == -1)
			return (va_end(ap), -1);
		else
			count++;
	}
	va_end(ap);
	return (count);
}
