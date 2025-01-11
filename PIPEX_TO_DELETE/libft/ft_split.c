/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:13:02 by pbuchter          #+#    #+#             */
/*   Updated: 2024/11/15 19:09:03 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//split string into 'words' with specified delimiter character c
#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != c) && (i == 0 || str[i - 1] == c))
			words++;
		i++;
	}
	return (words);
}

static void	write_word(char *dest, char const *from, char c)
{
	int	i;

	i = 0;
	while (from[i] != c && from[i] != '\0')
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static void	free_split(char **split, int word)
{
	while (word > 0)
		free (split[--word]);
	free(split);
}

static int	write_split(char **split, char const *str, char c)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			j = 0;
			while (str[i + j] != c && str[i + j] != '\0')
				j++;
			split[word] = (char *)malloc(sizeof (char) * (j + 1));
			if (!split[word])
				return (free_split(split, word), -1);
			write_word(split[word], str + i, c);
			i += j;
			word++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	result[words] = NULL;
	if (write_split(result, s, c) == -1)
	{
		return (NULL);
	}
	return (result);
}
// #include <unistd.h>

// int	main(void)
// {
// 	char		**result;
// 	char const	*str = "a1 a  222aa 3333aa";
// 	char		c = 'a';

// 	int	i = -1;
// 	int	j = -1;

// 	result = ft_split(str, c);
// 	if (result == NULL)
// 		return (0);
// 	while (result[++i])
// 	{
// 		j = -1;
// 		while (result[i][++j] != '\0')
// 		{
// 			write(1, &result[i][j], 1);
// 		}
// 		write(1, "\n", 1);
// 	}
// 	return (0);
// }
