#include "get_next_line.h"

void	free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		len = 0;
		start = 0;
	}
	else if (start + len > slen)
		len = slen - start;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	total_len;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len + 1;
	result = (char *)malloc(sizeof(char) * total_len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, s2, s2_len + 1);
	return (result);
}
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*(src + i) && size && i < size - 1)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (size)
		*(dst + i) = '\0';
	return (ft_strlen(src));
}
size_t	ft_strlen(const char	*s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len])
		len++;
	return (len);
}
ssize_t	ft_strnat(const char *str, int c, ssize_t n)
{
	char	*s1;
	ssize_t	i;

	if (!str)
		return (-1);
	i = 0;
	s1 = (char *) str;
	while (s1[i] && i < n)
	{
		if(s1[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
