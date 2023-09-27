#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# include <stdio.h> // REMOVE THIS
# include <fcntl.h> // REMOVE THIS
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct	s_buffer
{
	char	*content;
	size_t	len;
}				t_buffer;

char	*get_next_line(int fd);
// utils:
void	free_and_null(void **ptr);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char	*s);
ssize_t	ft_strnat(const char *str, int c, ssize_t n);

#endif
