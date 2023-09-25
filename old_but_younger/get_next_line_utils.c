
#include "get_next_line.h"

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

size_t	ft_strlen(const char	*s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
void	*ft_memset(void	*s, int c, size_t n)
{
	while (n--)
	{
		*(char *)(s + n) = c;
	}
	return (s);
}
int	ft_strnat(const char *str, int c, size_t n)
{
	char	*s1;
	int	i;

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

void	*ft_memmove(void	*dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src > dest)
	{
		while (i < n)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i++;
		}
	}
	else if (src < dest)
	{
		while (n--)
			*(char *)(dest + n) = *(char *)(src + n);
	}
	return (dest);
}
