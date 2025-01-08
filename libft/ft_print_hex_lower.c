/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:37:15 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/01 11:27:07 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex_lower(va_list *ap)
{
	return (ft_putnbr_base(va_arg(*ap, unsigned int), "0123456789abcdef"));
}
