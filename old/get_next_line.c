/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:21:48 by tkasbari          #+#    #+#             */
/*   Updated: 2023/09/23 10:40:59 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
static void	print_t_line(t_line *gline)
{
	printf("line_content: %s\n", gline->content);
	printf("line_len: %lu\n", gline->len);
	printf("line_bytes_allocated: %lu\n", gline->bytes_allocated);
	printf("line_eol_found: %i\n\n", gline->eol_found);
}
static void	print_t_buffer(t_buffer *lbuffer)
{
	printf("buffer_content: %s\n", lbuffer->content);
	printf("buffer_len: %lu\n", lbuffer->len);
	printf("buffer_eol_index: %lu\n", lbuffer->eol_index);
}
*/

/*
static void	*error_exit(t_line *gline)
{
	printf("error_exit(): freeing gline...\n");
	if (gline->content)
		free(gline->content);
	return (NULL);
}*/

static int	read_next_chunk(t_buffer *lbuffer, int fd)
{
	ssize_t	bytes_read;

	//bytes_read = NO_NEW_LINE;
	bytes_read = read(fd, lbuffer->content, BUFFER_SIZE);
	if (bytes_read >= 0)
		lbuffer->len = bytes_read;
	lbuffer->eol_index = ft_strnat(lbuffer->content, '\n', lbuffer->len);
	return (bytes_read);
}

static int	grow_line(t_line *gline, t_buffer *lbuffer)
{
	char	*new_alloc;

	if ((gline->len + lbuffer->len) > gline->bytes_allocated - 1)
	{
		//new_alloc = (char *)malloc(sizeof(char) * (gline->bytes_allocated + MALLOC_SIZE));
		new_alloc = (char *)ft_calloc(sizeof(char), (gline->bytes_allocated + MALLOC_SIZE));
		if (!new_alloc){
			free(gline->content);
			return (0);
		}
		ft_memmove(new_alloc, gline->content, gline->len);
		free(gline->content);
		gline->content = new_alloc;
		gline->bytes_allocated += MALLOC_SIZE;
	}
	if (lbuffer->eol_index == NO_NEW_LINE)
	{
		ft_memmove((void*)(gline->content + gline->len), (void*)lbuffer->content, lbuffer->len);
		gline->len += lbuffer->len;
		gline->eol_found = 0;
		lbuffer->len = 0;
		ft_memset((void*)lbuffer->content, '\0', BUFFER_SIZE);
	}
	else
	{
		ft_memmove((void*)(gline->content + gline->len), (void*)lbuffer->content, lbuffer->eol_index + 1);
		gline->len += lbuffer->eol_index + 1;
		gline->eol_found = 1;
		lbuffer->len -= (lbuffer->eol_index + 1);
		ft_memmove((void*)lbuffer->content, ((void*)lbuffer->content + lbuffer->eol_index + 1), lbuffer->len);
		ft_memset((void*)(lbuffer->content + lbuffer->len), '\0', BUFFER_SIZE - lbuffer->len);
		lbuffer->eol_index = ft_strnat(lbuffer->content, '\n', lbuffer->len);
	}
	return (1);
}

static char	*get_nl_buffer(t_buffer *lbuffer)
{
	char	*buffer_line;
	size_t	nbytes;

	nbytes = ft_strnat(lbuffer->content, '\n', lbuffer->len) + 1;
	if (nbytes == 0)
		nbytes = lbuffer->len;
	buffer_line = malloc(sizeof(char)*(nbytes + 1));
	if (!buffer_line)
		return (NULL);
	ft_memmove((void*)buffer_line, (void*)lbuffer->content, nbytes);
	buffer_line[nbytes] = '\0';
	ft_memmove((void*)lbuffer->content, (void*)(lbuffer->content + nbytes), lbuffer->len - nbytes);
	lbuffer->len -= nbytes;
	lbuffer->eol_index = ft_strnat(lbuffer->content, '\n', lbuffer->len);
	return (buffer_line);
}
char	*get_next_line(int fd)
{
	static t_buffer	lbuffer;
	t_line			growing_line;
	int				read_result;

	//if (BUFFER_SIZE <= 0)
	//	return (NULL);
	if (!lbuffer.len)
		read_next_chunk(&lbuffer, fd);
	if (!lbuffer.len)
		return (NULL);
	read_result = 0;
	if (lbuffer.eol_index != NO_NEW_LINE)
		return (get_nl_buffer(&lbuffer));
	//growing_line.content = malloc(sizeof(t_line) * MALLOC_SIZE);
	growing_line.content = ft_calloc(sizeof(t_line),  MALLOC_SIZE);
	if (!growing_line.content)
		return (NULL);
	growing_line.len = 0;
	growing_line.bytes_allocated = MALLOC_SIZE;
	growing_line.eol_found = 0;
	while (lbuffer.len && !growing_line.eol_found)
	{
		if (!grow_line(&growing_line, &lbuffer))
			return (NULL);
		if (!lbuffer.len)
		{
			read_result = read_next_chunk(&lbuffer, fd);
			if (read_result < 0)
			{
				free(growing_line.content);
				return (NULL);
			}
			if (read_result == 0)
			{
				return(growing_line.content);
			}
		}
	}
	return (growing_line.content);
}
