
#include "libft.h"

int	main(void)
{
	int		fd = open("test.txt", O_RDONLY);
	char	*line;

	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		write(1, line, ft_strlen(line));
		free(line);
	}
	close (fd);
	return (0);
}

int	main(void)
{
	char	*str;

	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	//close(fd);
}


