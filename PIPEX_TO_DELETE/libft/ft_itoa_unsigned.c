/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:23:50 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/01 11:27:51 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//converts integer to array
#include "libft.h"

static int	count_digits(unsigned int n);
static void	allocate_result(char *result, unsigned int n, int digits);

char	*ft_itoa_unsigned(unsigned int n)
{
	int		digits;
	char	*result;

	digits = count_digits(n);
	result = malloc((digits + 1) * sizeof (char));
	if (!result)
		return (0);
	result[digits] = '\0';
	allocate_result(result, n, digits);
	return (result);
}

static void	allocate_result(char *result, unsigned int n, int digits)
{
	int	i;

	i = 1;
	while (digits - i >= 0)
	{
		result[digits - i] = n % 10 + '0';
		n /= 10;
		i++;
	}
}

static int	count_digits(unsigned int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}
// #include <stdio.h>
// #include <limits.h>
// int	main(void)
// {
// 	unsigned int	n;
// 	n = -42;
// 	printf("%s\n", ft_itoa_unsigned(n));
// 	return (0);
// }
