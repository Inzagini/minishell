/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_upper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:38:17 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/01 11:27:10 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex_upper(va_list *ap)
{
	return (ft_putnbr_base(va_arg(*ap, unsigned int), "0123456789ABCDEF"));
}
