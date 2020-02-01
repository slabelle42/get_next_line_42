#include "get_next_line.h"

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	join_len;
	char	*join;
	int		i;
	int		j;

	join_len = gnl_strlen(s1) + gnl_strlen(s2) + 1;
	if (!(join = malloc(sizeof(char) * join_len)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

size_t	gnl_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*gnl_strdup(const char *src)
{
	size_t	dst_len;
	char	*dst;
	int		i;

	dst_len = gnl_strlen(src) + 1;
	if (!(dst = malloc(sizeof(char) * dst_len)))
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!(sub = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	if (!(start > gnl_strlen(s)))
	{
		while (s[start] && i < len)
			sub[i++] = s[start++];
	}
	sub[i] = '\0';
	return (sub);
}
