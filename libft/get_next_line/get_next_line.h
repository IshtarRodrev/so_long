/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:39:24 by akechedz          #+#    #+#             */
/*   Updated: 2025/10/16 10:18:34 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
#include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

#ifdef _WIN32
	#include <io.h>
	#include <fcntl.h>
	#define open _open
	#define read _read
	#define write _write
	#define close _close
	#define O_RDONLY _O_RDONLY
#else
	#include <unistd.h>
	#include <fcntl.h>
#endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
char	*ft_strchr(const char *str, int c);
// void	ft_bzero(void *s, size_t n);

#endif