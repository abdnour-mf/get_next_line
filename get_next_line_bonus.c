#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

# define BUFFER_SIZE 5
# define MAX_FD 1024

char *read_and_fill(int fd, char *remain)
{
	char *buffer;
	ssize_t bytes_read;
	
	buffer = malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return (free(remain), NULL);
	bytes_read = 1;
	while ((!remain || !ft_strchr(remain, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(remain), NULL);
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		remain = join_free(remain, buffer);
		if (!remain)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (remain);
}

static char *extract_line(char *remain)
{
	size_t i;
	char *line;

	if (!remain || remain[0] == '\0')
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (remain[i] == '\n')
		i++;
	line = ft_substr(remain, 0, i);
	if (!line)
		return (NULL);
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
		return (NULL);
	remain[fd] = read_and_fill(fd, remain[fd]);
	if (!remain[fd])
		return (NULL);
	line = extract_line(remain[fd]);
	remain[fd] = update_remain(remain[fd]);
	return (line);
}
#include <fcntl.h>

int main()
{
	int fd[3];
	char *line;

	fd[0] = open("test.txt", O_RDONLY);
	fd[1] = open("test2.txt", O_RDONLY);
	fd[2] = open("test3.txt", O_RDONLY);


	int i = 0;

	while (i < 3)
	{
		while((line = get_next_line(fd[i])))
		{
			printf("%s", line);
			free(line);
		}
		close(fd[i]);
		i++;
	}

	/* while (line = get_next_line(fd3))
	{
		printf("%s", line);
		free(line);
	}
	while (line = get_next_line(fd4))
	{
		printf("%s", line);
		free(line);
	}
	while (line = get_next_line(fd5))
	{
		printf("%s", line);
		free(line);
	} */

	/* line = get_next_line(fd3);
	printf("%s", line);
	free(line);
	line = get_next_line(fd4);
	printf("%s", line);
	free(line);
	line = get_next_line(fd3);
	printf("%s", line);
	free(line);
	line = get_next_line(fd5);
	printf("%s", line);
	free(line);
	line = get_next_line(fd4);
	printf("%s", line);
	free(line); */
	
	return (0);
}