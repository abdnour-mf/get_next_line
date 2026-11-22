#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

static void	copy_all(char *dst, const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
}

char	*join_free(char *s1, char *s2)
{
	char	*str;

	if (!s2)
	{
		free(s1);
		return (NULL);
	}
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	copy_all(str, s1, s2);
	free(s1);
	return (str);
}