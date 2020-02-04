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
	char			buffer[BUFFER_SIZE + 1];
	int				nbytes;

	to_free2 = save;
	while ((nbytes = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[nbytes] = '\0';
		save = gnl_strjoin(save, buffer);
	}
	free(to_free2);
	return (save);
}

int		gnl_verify_errors_malloc(int fd, char **line, char **save)
{
	if (fd == -1 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!*save)
	{
		if (!(*save = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char		*save;
	int				i;
	char			*to_free1;

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
