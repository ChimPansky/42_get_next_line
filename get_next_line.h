/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:49:42 by tkasbari          #+#    #+#             */
/*   Updated: 2023/09/28 20:59:44 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer
{
	char	*cont;
	ssize_t	len;
	ssize_t	last_read;
}				t_buffer;

char	*get_next_line(int fd);
void	free_and_null(void **ptr);
void	*ft_memmove(void *dest, const void *src, size_t n);

#endif
