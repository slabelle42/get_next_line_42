/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:37:14 by slabelle          #+#    #+#             */
/*   Updated: 2020/02/10 15:51:02 by slabelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_and_null(char **to_free)
{
	if (to_free && *to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

char	*join_buffer(char *save, char *buffer)
{
	size_t			len_buffer;
	size_t			len_save;
	size_t			len;
	char			*join;

	len_buffer = gnl_strlen(buffer);
	len_save = 0;
	if (save)
		len_save = gnl_strlen(save);
	len = len_buffer + len_save;
	if (!(join = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (save)
	{
		gnl_strlcpy(join, save, (len_save + 1));
		free_and_null(&save);
	}
	gnl_strlcpy((join + len_save), buffer, (len_buffer + 1));
	return (join);
}

int		line_saved(char **save, char **line)
{
	char			*found;
	size_t			end;
	size_t			len;

	found = NULL;
	if ((found = gnl_strchr(*save, '\n')))
	{
		end = found - *save;
		len = gnl_strlen(found);
		*line = gnl_substr(*save, 0, end);
		gnl_strlcpy(*save, (found + 1), (len + 1));
		return (1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char			*buffer[BUFFER_SIZE + 1];
	static char		*save;
	int				nbytes;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (save && line_saved(&save, line))
		return (1);
	while ((nbytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[nbytes] = '\0';
		if (!(save = join_buffer(save, buffer)))
			return (-1);
		if (line_saved(&save, line))
			return (1);
	}
	if (save && *save)
		*line = gnl_strdup(save);
	else if (nbytes == 0)
		*line = gnl_strdup("");
	free_and_null(&save);
	return (nbytes);
}
