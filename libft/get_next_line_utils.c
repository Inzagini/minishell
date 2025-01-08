/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:28:10 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/21 12:37:24 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *buffer, char *reader)
{
	char	*result;
	size_t	i;
	size_t	buffer_length;
	size_t	reader_length;

	if (!buffer)
		buffer = ft_initialize_buffer();
	if (!reader || !buffer)
		return (buffer);
	buffer_length = ft_strlen(buffer);
	reader_length = ft_strlen(reader);
	result = malloc((buffer_length + reader_length + 1) * sizeof(char));
	if (!result)
		return (free (buffer), NULL);
	i = -1;
	while (++i < buffer_length)
		result[i] = buffer[i];
	i -= 1;
	while (++i < buffer_length + reader_length)
		result[i] = reader[i - buffer_length];
	result[i] = '\0';
	free(buffer);
	return (result);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	i = 0;
	uc = (unsigned char) c;
	if (!s)
		return (NULL);
	if (uc == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (s[i])
	{
		if (s[i] == uc)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	return (0);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_initialize_buffer(void)
{
	char	*buffer;

	buffer = malloc(1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	return (buffer);
}
