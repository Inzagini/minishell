/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:34:46 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:09:29 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//trim all characters in "set" from beginning and end of "s1"
#include "libft.h"

static	int		part_of(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		count_start;
	int		count_end;
	int		i;
	char	*result;

	len = 0;
	count_start = 0;
	count_end = 0;
	i = -1;
	while (part_of(s1[count_start], set))
		count_start++;
	len = (int) ft_strlen(s1);
	while (len - count_end - count_start >= 0
		&& part_of(s1[len - count_end -1], set))
		count_end++;
	if (count_start + count_end > len)
		len++;
	result = malloc((len - count_start - count_end + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (++i < len - count_start - count_end)
		result[i] = s1[count_start + i];
	result[i] = '\0';
	return (result);
}

static int	part_of(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char	*result;
// 	result = ft_strtrim("A  ABCDA", " A");
// 	printf("%s", result);
// 	free (result);
// 	return (0);
// }
