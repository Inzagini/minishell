/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:28:07 by pbuchter          #+#    #+#             */
/*   Updated: 2024/12/17 13:30:04 by pbuchter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_fill_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	next_line = ft_grab_line(buffer[fd]);
	buffer[fd] = ft_clear_line(buffer[fd]);
	return (next_line);
}

char	*ft_fill_buffer(int fd, char *buffer)
{
	int		bytes_read;
	char	*reader;

	reader = malloc(BUFFER_SIZE + 1);
	if (!reader)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr_gnl(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, reader, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (reader);
			free (buffer);
			return (NULL);
		}
		reader[bytes_read] = 0;
		buffer = ft_strjoin_gnl(buffer, reader);
	}
	free (reader);
	return (buffer);
}

char	*ft_grab_line(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = malloc(i + 2);
	else
		line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = -1;
	while (++j < i)
		line[j] = buffer[j];
	if (buffer[j] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_clear_line(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;
	int		buffer_length;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free (buffer);
		return (NULL);
	}
	buffer_length = ft_strlen(buffer);
	new_buffer = malloc(buffer_length - i++);
	if (!new_buffer)
		return (free (buffer), NULL);
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free (buffer);
	return (new_buffer);
}
