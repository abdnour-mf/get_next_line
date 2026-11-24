#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include "get_next_line_bonus.h"


/*read first and last line*/
/* int main()
{
	int fd = open("test.txt", O_RDONLY);

	char *gnl;
	char *first;
	first = get_next_line(fd);
	printf("%s", first);


	char *last;
	last = NULL;

	gnl = get_next_line(fd);
	while (gnl)
	{
		free(last);
		last = gnl;
		gnl = get_next_line(fd);
	}
	printf("%s", last);
	free(first);
	free(last);
	free(gnl);
	close (fd);
} */

/* print all the fds*/
int main()
{
	int fd[3];

	fd[0] = open("test1.txt", O_RDONLY);
	fd[1] = open("test2.txt", O_RDONLY);
	fd[2] = open("test3.txt", O_RDONLY);

	char *line;
	int i = 0;
	while (i < 3)
	{
		line = get_next_line_bonus(fd[i]);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
		if (line == NULL)
			i++;
	}
}

/*print first line each fd*/
/* int main()
{
	int fd[3];
	fd[0] = open("test1.txt", O_RDONLY);
	fd[1] = open("test2.txt", O_RDONLY);
	fd[2] = open("test3.txt", O_RDONLY);

	char *line;
	int i = 0;
	while (i < 3)
	{
		line = get_next_line_bonus(fd[i]);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
		i++;
	}
	i = 0;
	while (i < 3)
	{
		line = get_next_line_bonus(fd[i]);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
		i++;
	}
} */

/*open more than Sn*/
/* int main(void)
{
    int fd;

    while (1)
    {
        fd = open("/dev/null", O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            break;
        }
        printf("Opened FD: %d\n", fd);
    }
    return (0);
} */

/*printf only pair lines*/
/* int main()
{
	int fd = open("test1.txt", O_RDONLY);
	char *gnl = get_next_line(fd);
	
	int i = 1;
	while(gnl)
	{
		if ((i % 2) == 0)
		{
			printf("%s", gnl);
			free(gnl);
		}
		gnl = get_next_line(fd);
		i++;
	}
} */

/*read the given lines*/
/* int main()
{
	int fd = open("test2.txt", O_RDONLY);
	int fd0 = open("test2.txt", O_RDONLY);
	char *gnl = get_next_line(fd);
	
	int i = 0;
	while(gnl)
	{
		i++;
		gnl = get_next_line(fd);
	}
	//printf("%d", i);
	close(fd);

	i = 0;
	gnl = get_next_line(fd0);
	while(gnl)
	{
		if (i == 1 || i == 2 || i == 4)
		{
			printf("%s", gnl);
			free(gnl);
		}
		i++;
		gnl = get_next_line(fd0);
	}
} */
