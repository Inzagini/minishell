/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:44:54 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:08:00 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//allocates memory for nmemb objects of size size and returns pointer to memory
//limit memory allocation to approx 1GB (had some leaks for very large values)
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((nmemb > ((size_t)-1) / size))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
// #include <stdio.h>
// #include <limits.h>
// int main()
// {
//		int *array = ft_calloc(1024 * 1024 * 1024, 1024);
//		int *array2 = calloc(INT_MAX, 1024);
//		if (array)
//		{
//			for (int i = 0; i < 5; i++)
//				printf("%d ", array[i]);
//		 	free(array);
//			free(array2);
//		}
//		return 0;
// }
