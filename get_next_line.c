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

static t_gnl	*buffer_check_nl(t_gnl *gnl)
{
	gnl->ptr = ft_strchr(gnl->buffer, '\n');
	if (gnl->ptr)
	{
		*gnl->ptr = '\0';
		gnl->line = ft_strappend(gnl->line, gnl->buffer);
		gnl->line = ft_strappend(gnl->line, "\n");
		ft_memmove(gnl->buffer, gnl->ptr + 1, ft_strlen(gnl->ptr + 1) + 1);
	}
	else
	{
		gnl->line = ft_strappend(gnl->line, gnl->buffer);
		gnl->buffer[0] = '\0';
	}
	return (gnl);
}

static t_gnl	*get_new_buffer(int fd, t_gnl *gnl)
{
	int	bytes_read;

	buffer_check_nl(gnl);
	if (gnl->ptr || !gnl->line)
		return (gnl);
	while (!gnl->ptr)
	{
		bytes_read = read(fd, gnl->buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(gnl->line);
			gnl->line = NULL;
			break ;
		}
		gnl->buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		buffer_check_nl(gnl);
	}
	return (gnl);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl[1024] = {{NULL, NULL, NULL}};

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl[fd].buffer)
	{
		gnl[fd].buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!gnl[fd].buffer)
			return (NULL);
		gnl[fd].buffer[0] = '\0';
	}
	gnl[fd].line = ft_strdup("");
	get_new_buffer(fd, &gnl[fd]);
	if (gnl[fd].line && gnl[fd].line[0] == '\0')
	{
		free(gnl[fd].line);
		gnl[fd].line = NULL;
	}
	if (!gnl[fd].line)
	{
		free(gnl[fd].buffer);
		gnl[fd].buffer = NULL;
	}
	return (gnl[fd].line);
}
