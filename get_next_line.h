/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:18:57 by alejhern          #+#    #+#             */
/*   Updated: 2024/08/06 14:19:02 by alejhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	char	*buffer;
	char	*line;
	char	*ptr;
}			t_gnl;

// Declarations from get_next_line_utils.c
void		*ft_memmove(void *dest, const void *src, size_t n);
char		*ft_strdup(const char *str);
char		*ft_strchr(const char *str, int c);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
// Declarations from get_next_line.c
char		*get_next_line(int fd);

#endif