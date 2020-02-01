#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*save;
	int				nbytes;
	int				i;

	if (fd < 0 || !line || read(fd, buffer, 0) < 0)
		return (-1);
	if (!save)
	{
		if (!(save = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
	}
	while ((nbytes = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[nbytes] = '\0';
		save = gnl_strjoin(save, buffer);
	}
	i = 0;
	if (save[i])
	{
		while (save[i] && save[i] != '\n')
			i++;
		*line = gnl_substr(save, 0, i);
		save = &save[i + 1];
		return (1);
	}
	*line = gnl_strdup("");
	return (0);
}
