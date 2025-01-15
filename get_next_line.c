/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:21:14 by alejhern          #+#    #+#             */
/*   Updated: 2024/08/09 11:12:45 by alejhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strappend(char *dest, char *to_append)
{
	size_t	dest_len;
	size_t	to_append_len;
	char	*new_str;

	if (!dest && !to_append)
		return (NULL);
	if (!to_append)
		return (dest);
	if (!dest)
		return (ft_strdup(to_append));
	dest_len = ft_strlen(dest);
	to_append_len = ft_strlen(to_append);
	new_str = (char *)malloc(dest_len + to_append_len + 1 * sizeof(char));
	if (!new_str)
	{
		free(dest);
		return (NULL);
	}
	ft_strlcpy(new_str, dest, dest_len + 1);
	free(dest);
	ft_strlcpy(new_str + dest_len, to_append, to_append_len + 1);
	new_str[dest_len + to_append_len] = '\0';
	return (new_str);
}

static char	**buffer_check_nl(char **buffer)
{
	buffer[2] = ft_strchr(buffer[1], '\n');
	if (buffer[2])
	{
		*buffer[2] = '\0';
		buffer[0] = ft_strappend(buffer[0], buffer[1]);
		buffer[0] = ft_strappend(buffer[0], "\n");
		ft_memmove(buffer[1], buffer[2] + 1, ft_strlen(buffer[2] + 1) + 1);
	}
	else
	{
		buffer[0] = ft_strappend(buffer[0], buffer[1]);
		*buffer[1] = '\0';
	}
	return (buffer);
}

static char	**get_new_buffer(int fd, char **buffer)
{
	int	bytes_read;

	buffer_check_nl(buffer);
	if (buffer[2] || !buffer[0])
		return (buffer);
	while (!buffer[2])
	{
		bytes_read = read(fd, buffer[1], BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer[0]);
			buffer[0] = NULL;
			break ;
		}
		buffer[1][bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		buffer_check_nl(buffer);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024][4] = {{NULL}};

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd][1])
	{
		buffer[fd][1] = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
		if (!buffer[fd][1])
			return (NULL);
		buffer[fd][1][0] = '\0';
	}
	buffer[fd][0] = ft_strdup("");
	get_new_buffer(fd, buffer[fd]);
	if (buffer[fd][0] && buffer[fd][0][0] == '\0')
	{
		free(buffer[fd][0]);
		buffer[fd][0] = NULL;
	}
	if (!buffer[fd][0])
	{
		free(buffer[fd][1]);
		buffer[fd][1] = NULL;
	}
	return (buffer[fd][0]);
}
