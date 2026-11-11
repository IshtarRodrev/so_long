/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:47:44 by akechedz          #+#    #+#             */
/*   Updated: 2025/12/04 17:36:24 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static int	clean_buffer(char *buffer)
{
	char	*line;
	size_t	n;

	n = 0;
	line = ft_strchr(buffer, '\n');
	if (!line)
	{
		buffer[0] = '\0';
		return (0);
	}
	line++;
	if (*line == '\0')
	{
		buffer[0] = '\0';
		return (0);
	}
	while (line[n] != '\0')
	{
		buffer[n] = line[n];
		n++;
	}
	buffer[n] = '\0';
	return (1);
}

static char	*extract_line(char *input)
{
	char	*line;
	size_t	n;

	n = 0;
	while (input[n] && input[n] != '\n')
		n++;
	if (input[n] == '\n')
		n++;
	line = malloc((n + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, input, n + 1);
	return (line);
}

static char	*read_input(char *buffer, int fd)
{
	char	*line;
	ssize_t	nbyte;
	char	*joined;

	line = ft_strjoin(buffer, "");
	if (line == NULL)
		return (NULL);
	if (ft_strchr(line, '\n') != NULL)
		return (line);
	nbyte = read(fd, buffer, BUFFER_SIZE);
	while (nbyte > 0)
	{
		buffer[nbyte] = '\0';
		joined = ft_strjoin(line, buffer);
		if (!joined)
			return (free(line), NULL);
		free(line);
		line = joined;
		if (ft_strchr(line, '\n') != NULL)
			return (line);
		nbyte = read(fd, buffer, BUFFER_SIZE);
	}
	if (nbyte == -1)
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*input;
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	input = read_input(buffer, fd);
	if (!input)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	output = extract_line(input);
	free(input);
	if (!output)
		return (buffer[0] = '\0', NULL);
	clean_buffer(buffer);
	if (output[0] == '\0')
	{
		free(output);
		buffer[0] = '\0';
		return (NULL);
	}
	return (output);
}
