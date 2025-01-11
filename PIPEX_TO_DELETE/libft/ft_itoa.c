/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:15:40 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:08:22 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//converts integer to array
#include "libft.h"

static int	count_digits(long n);
static void	allocate_result(char *result, int isneg, long nbr, int digits);

char	*ft_itoa(int n)
{
	int		digits;
	int		isneg;
	char	*result;
	long	nbr;

	nbr = (long) n;
	isneg = 0;
	if (nbr < 0)
	{
		isneg = 1;
		nbr = nbr * (-1);
	}
	digits = count_digits(nbr);
	result = malloc((digits + isneg + 1) * sizeof (char));
	if (!result)
		return (0);
	if (isneg)
		result[0] = '-';
	result[digits + isneg] = '\0';
	allocate_result(result, isneg, nbr, digits);
	return (result);
}

static void	allocate_result(char *result, int isneg, long nbr, int digits)
{
	int	i;

	i = 1;
	while (digits - i >= 0)
	{
		result[digits + isneg - i] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
}

static int	count_digits(long n)
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
// 	int	n;
// 	n = INT_MIN;
// 	printf("%s\n", ft_itoa(n));
// 	return (0);
// }
