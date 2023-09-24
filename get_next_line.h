#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h> // REMOVE THIS!!!
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Struct for storing the bytes read with read()
// End of Line Index: Index of \n Character
// (or last char if End of File).
typedef struct s_buffer
{
	char	content[BUFFER_SIZE];
	size_t	len;
	int		nl_ind;
	int		ready_to_print;
}				t_buffer;

// Struct for storing a line, that is greater than BUFFER_SIZE
typedef struct s_line
{
	char	*content;
	size_t	len;
	int		eol_ind;
	size_t	allocated;
	int		ready_to_print;
}				t_line;

char	*get_next_line(int fd);

void	ft_putchar_fd(char c, int fd); // REMOVE THIS
void	ft_putnbr_fd(int n, int fd); // REMOVE THIS
size_t	ft_strlen(const char	*s); // REMOVE THIS
void	ft_putstr_fd(char *s, int fd); // REMOVE THIS

void	*ft_memset(void	*s, int c, size_t n);
int		ft_strnat(const char *str, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memmove(void	*dest, const void *src, size_t n);

#endif
