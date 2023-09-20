/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:21:53 by tkasbari          #+#    #+#             */
/*   Updated: 2023/09/20 10:13:12 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define NO_NEW_LINE (size_t) (-1)

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# define MALLOC_SIZE BUFFER_SIZE

typedef struct s_line
{
	char	*content;
	size_t	len;
	size_t	bytes_allocated;
	int		eol_found;
}				t_line;

typedef struct s_buffer
{
	char	content[BUFFER_SIZE];
	size_t	len;
	size_t	eol_index;
}				t_buffer;

char	*get_next_line(int fd);
size_t	ft_strnat(const char *str, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void	*s, int c, size_t n);
void	*ft_memmove(void	*dest, const void *src, size_t n);



#endif
