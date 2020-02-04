/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slabelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:37:14 by slabelle          #+#    #+#             */
/*   Updated: 2020/02/01 18:37:16 by slabelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_join_and_free(int fd, char *save)
{
	char			*to_free2;

	to_free2 = save;

	free(to_free2);
	return (save);
}

int		gnl_verify_errors_malloc(int fd, char **line, char **save)
{

	if (!*save)
	{
		if (!(*save = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
	}
	return (0);
}

// -----------------------------------------------------

char	*join_and_free(char *save, char *buffer)
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
		free(save);
	}
	gnl_strlcpy((join + len_save), buffer, (len_buffer + 1));
	return (join);
}

int 	is_line(char **save, char **line)
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
	static char		*save;
	int				nbytes;
	char			buffer[BUFFER_SIZE + 1];

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (save && is_line(&save, line))
		return (1);
	while ((nbytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[nbytes] = '\0';
		if (!(save = join_and_free(save, buffer)))
			return (-1);
		if (is_line(&save, line))
			return (1);
	}

// -----------------------------------------------------
	if (gnl_verify_errors_malloc(fd, line, &save) == -1)
		return (-1);

	save = gnl_join_and_free(fd, save);
	i = 0;
	if (save[i])
	{
		while (save[i] && save[i] != '\n')
			i++;
		if (i == 0)
			*line = gnl_strdup("");
		*line = gnl_substr(save, 0, i);
		to_free1 = save;
		save = &save[i + 1];
		free(to_free1);
		return (1);
	}
	*line = gnl_strdup("");
	return (0);
}
