#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

# define BUFFER_SIZE 5

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	static char	*remain;
	char		*full;

	//here we give the REMAIN to FULL
	if (remain)
	{
		full = ft_strdup(remain);
		free(remain);
		remain = NULL;
	}
	//in the first call we set full as empty string
	else
		full = ft_strdup("");
	if (!full)
		return (NULL);

	char	*buffer;
	//allocate buffer with buffer_size + \0
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(full);
		return (NULL);
	}

	ssize_t	bytes_read = 1;
	char	*tmp;

	//while we didn't reach the end of file
	//the first condition in case we read too many lines (big BUFFER_SIZE)
	//so we don't need to read again since we wanna print one line at a time
	while (!ft_strchr(full, '\n') && (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		//we add the \0 at the end of each returned value since read only gets bytes
		buffer[bytes_read] = '\0';

		//we add a tmp string to give it what we had + what we read
		//we can't just "full = join_free(full, buffer)" cause we wouldn't free full
		//this way, that may cause memory leak
		tmp = join_free(full, buffer);
		/* if (!tmp)
		{
			free(full);
			free(buffer);
			remain = NULL;
			return (NULL);
		} */
		free(full);
		full = tmp;
		//after freeing the old data from full, we give it that data + what read read
	}

	if (bytes_read < 0)
	{
		free(full);
		free(buffer);
		remain = NULL;
		return (NULL);
	}
	free(buffer);

	//here in the case we reached the EOF and there is nothing left more to read, we return NULL
	if (bytes_read == 0 && full[0] == '\0')
	{
		free(full);
		remain = NULL;
		return (NULL);
	}

	//here if we are in the last line (doesn't have \n), so we return that line directly
	if (bytes_read == 0 && !ft_strchr(full, '\n') && full[0] != '\0')
	{
		char	*line = ft_strdup(full);
		free(full);
		remain = NULL;
		return (line);
	}

	int		i = 0;
	int		len = ft_strlen(full);
	char	*line = NULL;

	//read till the end of the line
	while (full[i] && full[i] != '\n')
		i++;

	//allocate enough memory for both line and remain
	if (full[i] == '\n')
	{
		line = malloc(i + 2);
		if (!line)
		{
			free(full);
			return (NULL);
		}
		//here we check if there is still bytes after that line
		//if not we set remain at NULL since it is the last line
		if (full[i + 1] != '\0')
		{
			remain = malloc(len - i);
			if (!remain)
			{
				free(line);
				free(full);
				return (NULL);
			}
		}
		else
			remain = NULL;
	}
	else
	{
		line = malloc(i + 1);
		if (!line)
		{
			free(full);
			return (NULL);
		}
		remain = NULL;
	}

	i = 0;
	//we copy that line to LINE
	while (full[i] && full[i] != '\n')
	{
		line[i] = full[i];
		i++;
	}

	//if there is still a newline, we add \n and \0; if not, only \0
	if (full[i] == '\n')
	{
		line[i] = '\n';
		i++;
		line[i] = '\0';
	}
	else
		line[i] = '\0';

	int	j = 0;
	//here we copy the remaining into REMAIN
	while (remain && full[i])
	{
		remain[j] = full[i];
		i++;
		j++;
	}
	if (remain)
		remain[j] = '\0';

	free(full);
	return (line);
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *hh;
	while (hh = get_next_line(fd))
	{
		printf("%s", hh);
		free(hh);
	}
	printf("%s\n", hh);
	//printf("EOF reached cleanly without segfault!\n");
	close (fd);
}
