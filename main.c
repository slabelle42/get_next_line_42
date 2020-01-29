#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int		main(int ac, char **av)
{
	int		ret;
	char	*line;
	int		fd;
	int		fd2;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		fd2 = open("text.txt", O_RDONLY);
		ret = get_next_line(fd, &line);
		printf("GNL returned -> %d\n", ret);
		printf("Obtained line is: %s\n", line);
		ret = get_next_line(fd2, &line);
		printf("GNL returned -> %d\n", ret);
		printf("Obtained line is: %s\n", line);
		ret = get_next_line(fd, &line);
		printf("GNL returned -> %d\n", ret);
		printf("Obtained line is: %s\n", line);
		ret = get_next_line(fd2, &line);
		printf("GNL returned -> %d\n", ret);
		printf("Obtained line is: %s\n", line);
		ret = get_next_line(fd, &line);
		printf("GNL returned -> %d\n", ret);
		printf("Obtained line is: %s\n", line);
		ret = get_next_line(fd2, &line);
		printf("GNL returned -> %d\n", ret);
		printf("Obtained line is: %s\n", line);
	}
	return (0);
}	