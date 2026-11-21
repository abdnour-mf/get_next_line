#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

# define BUFFER_SIZE 5

static char *read_and_fill(int fd, char *remain)
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

char *get_next_line(int fd)
{
	static char *remain;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remain = read_and_fill(fd, remain);
	if (!remain)
		return (NULL);
	line = extract_line(remain);
	remain = update_remain(remain);
	return (line);
}

#include <fcntl.h>

int main()
{
	for (int fd)
	int fd = open("test.txt", O_WRONLY);
	char *hh;
	while ((hh = get_next_line(fd)))
	{
		printf("%s", hh);
		free(hh);
	}
	printf("%p\n", (void *)hh);
	close (fd);
}