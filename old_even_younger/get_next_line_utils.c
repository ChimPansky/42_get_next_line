#include "get_next_line.h"



char	*ft_strchr(const char *s, int c)
{
	char				*str;
	const unsigned char	my_c = (const unsigned char) c;

	str = (char *)s;
	while (*str)
	{
		if (*str == my_c)
			return (str);
		str++;
	}
	if (!my_c)
		return (str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
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
	result = (char *)ft_calloc(sizeof(char), total_len);
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
	result = (char *)ft_calloc(sizeof(char), len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	total_size;
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	i = 0;
	total_size = nmemb * size;
	if (total_size / nmemb != size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	while (i < total_size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

size_t	ft_strlen(const char	*s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nr;

	nr = (long) n;
	if (nr < 0)
	{
		ft_putchar_fd('-', fd);
		nr *= -1;
	}
	if (nr >= 10)
	{
		ft_putnbr_fd(nr / 10, fd);
		ft_putnbr_fd(nr % 10, fd);
	}
	if (nr < 10)
		ft_putchar_fd('0' + nr, fd);
}



void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
