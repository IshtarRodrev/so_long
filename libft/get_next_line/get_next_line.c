/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:47:44 by akechedz          #+#    #+#             */
/*   Updated: 2026/06/05 00:00:00 by GitHub Copilot  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
# include <unistd.h>
# include <stdlib.h>

static char *join_remainder(char *remainder, const char *buffer)
{
    char *next;

    if (!remainder)
        return ft_strdup(buffer);
    next = ft_strjoin(remainder, buffer);
    free(remainder);
    return next;
}

static char *extract_line(const char *remainder)
{
    size_t len;
    char *newline;
    char *line;

    if (!remainder)
        return NULL;
    newline = ft_strchr(remainder, '\n');
    if (newline)
        len = newline - remainder + 1;
    else
        len = ft_strlen(remainder);
    line = ft_substr(remainder, 0, len);
    return line;
}

static char *save_remainder(char *remainder)
{
    char *newline;
    char *next;

    if (!remainder)
        return NULL;
    newline = ft_strchr(remainder, '\n');
    if (!newline)
    {
        free(remainder);
        return NULL;
    }
    next = ft_strdup(newline + 1);
    free(remainder);
    return next;
}

char *get_next_line(int fd)
{
    static char *remainder;
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    while (!remainder || !ft_strchr(remainder, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            break;
        buffer[bytes_read] = '\0';
        remainder = join_remainder(remainder, buffer);
        if (!remainder)
            return NULL;
    }
    if (!remainder || *remainder == '\0')
    {
        free(remainder);
        remainder = NULL;
        return NULL;
    }
    {
        char *line = extract_line(remainder);

        remainder = save_remainder(remainder);
        return line;
    }
}
