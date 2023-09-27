#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h> // REMOVE THIS
# include <fcntl.h> // REMOVE THIS
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE
# endif


char	*get_next_line(int fd);

// Utils:
void	*ft_calloc(size_t nmemb, size_t size); // mb replace with mallocs??
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char	*s);

void	ft_putchar_fd(char c, int fd); // REMOVE THIS
void	ft_putnbr_fd(int n, int fd); // REMOVE THIS

void	ft_putstr_fd(char *s, int fd); // REMOVE THIS

#endif
