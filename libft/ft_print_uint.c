/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:34:56 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/01 11:27:27 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_uint(va_list *ap)
{
	unsigned int	num;
	char			*output;
	int				i;

	i = 0;
	num = va_arg(*ap, unsigned int);
	output = ft_itoa_unsigned(num);
	if (!output)
		return (-1);
	while (output[i])
		if (write(1, &output[i++], 1) == (-1))
			return (free (output), -1);
	free (output);
	return (i);
}
