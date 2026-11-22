/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amfarrej <amfarrej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 22:11:33 by amfarrej          #+#    #+#             */
/*   Updated: 2026/11/22 01:26:52 by amfarrej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_and_fill(int fd, char *remain)
{
	char *buffer;
	ssize_t bytes_read;
	
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(remain), NULL);
	bytes_read = 1; // to enter the loop at the first iteration
	while (!ft_strchr(remain, '\n') && bytes_read > 0)
	{
		
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(remain), free(buffer), NULL);
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';	
		remain = join_free(remain, buffer);
		if (!remain)
			return (free(remain), NULL);
	}
	free (buffer);
	return (remain);
}

static char *extract_line(char *remain)
{
	size_t i;
	size_t j;
	char *line;
	
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

static char *update_remain(char *remain)
{
	size_t i;
	char *rest;

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
	static char *remain;
	char *line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		{
   			free(remain);
   			return ((remain = NULL), remain);
		}
	remain = read_and_fill(fd, remain);
	if (!remain)
		return (NULL);
	line = extract_line(remain);
	if (!line)
	{
		free(remain);
   		return ((remain = NULL), remain);
	}
	remain = update_remain(remain);
	return (line);
}

/* #include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd = open("test.txt", O_CREAT | O_RDONLY, 0644);
	char *gnl = get_next_line(fd);

	while(gnl)
	{
		printf("%s", gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
	close(fd);
} */
