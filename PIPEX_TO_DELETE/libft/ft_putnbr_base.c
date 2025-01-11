/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:43:55 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/01 11:27:41 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned long nbr, char *base)
{
	char	result[17];
	int		index;
	int		length;

	index = 0;
	if (nbr == 0)
	{
		if (write(1, "0", 1) == (-1))
			return (-1);
		return (1);
	}
	while (nbr > 0)
	{
		result[index++] = base[nbr % 16];
		nbr = nbr / 16;
	}
	length = index;
	while (--index >= 0)
		if (write(1, &result[index], 1) == -1)
			return (-1);
	return (length);
}
