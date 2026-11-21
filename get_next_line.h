#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*join_free(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char *ft_substr(char const *s, unsigned int start, size_t len);

#endif