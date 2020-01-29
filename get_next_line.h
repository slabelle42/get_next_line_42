#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <io.h> //unistd.h

# define BUFFER_SIZE 32

int     get_next_line(int fd, char **line);
char	*gnl_strjoin(char const *s1, char const *s2);
size_t	gnl_strlen(const char *str);
char	*gnl_strcpy(char *dst, const char *src);

#endif