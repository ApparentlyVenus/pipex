/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:36:38 by odana             #+#    #+#             */
/*   Updated: 2025/06/16 12:25:01 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

static char	*fill_line_buffer(int fd, char *stash, char *buffer)
{
	ssize_t		bytes_read;
	char		*temp_stash;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp_stash = stash;
		stash = ft_strjoin(temp_stash, buffer);
		free(temp_stash);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

static char	*update_stash(char *stash)
{
	size_t	i;
	char	*line;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
		return (NULL);
	line = ft_substr(stash, i + 1, ft_strlen(stash) - (i + 1));
	if (!line)
		line = NULL;
	stash[i + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		free(stash);
		buffer = NULL;
		stash = NULL;
		return (NULL);
	}
	line = fill_line_buffer(fd, stash, buffer);
	free(buffer);
	buffer = NULL;
	if (!line || !*line)
	{
		free(line);
		return (NULL);
	}
	stash = update_stash(line);
	return (line);
}
