/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amfarrej <amfarrej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 00:41:02 by amfarrej          #+#    #+#             */
/*   Updated: 2026/11/22 16:38:45 by amfarrej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_fill(int fd, char *remain)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(remain), NULL);
	bytes_read = 1;
	while (!ft_strchr(remain, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(remain), free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		remain = join_free(remain, buffer);
		if (!remain)
			return (free(remain), NULL);
	}
	free(buffer);
	return (remain);
}

static char	*extract_line(char *remain)
{
	size_t	i;
	size_t	j;
	char	*line;

	if (remain[0] == '\0')
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (remain[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = remain[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*update_remain(char *remain)
{
	size_t	i;
	char	*rest;

	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (!remain[i])
		return (free(remain), NULL);
	i++;
	if (!remain[i])
		return (free(remain), NULL);
	rest = ft_strdup(remain + i);
	if (!rest)
		return (free(remain), NULL);
	free(remain);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*remain[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
	{
		free(remain[fd]);
		return ((remain[fd] = NULL), remain[fd]);
	}
	remain[fd] = read_and_fill(fd, remain[fd]);
	if (!remain[fd])
		return (NULL);
	line = extract_line(remain[fd]);
	if (!line)
	{
		free(remain[fd]);
		return ((remain[fd] = NULL), remain[fd]);
	}
	remain[fd] = update_remain(remain[fd]);
	return (line);
}
