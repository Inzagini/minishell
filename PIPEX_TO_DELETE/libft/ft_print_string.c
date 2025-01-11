/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:01 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/01 11:27:23 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_string(va_list *ap)
{
	char	*output;
	int		i;

	i = 0;
	output = va_arg(*ap, char *);
	if (!output)
		output = "(null)";
	while (output[i])
	{
		if (write(1, &output[i], 1) == (-1))
			return (-1);
		i++;
	}
	return (ft_strlen(output));
}
