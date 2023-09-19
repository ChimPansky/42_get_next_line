/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:21:48 by tkasbari          #+#    #+#             */
/*   Updated: 2023/09/19 11:30:02 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
static int	t_line_init(t_line *line)
{
	printf("t_line_init start \n");
	line->len = 0;
	line->eol_found = 0;
	line->bytes_allocated = MALLOC_SIZE;
	printf("t_line_init before callocing for content \n");
	line->content = (char *)ft_calloc(sizeof(char), MALLOC_SIZE);
	printf("t_line_init after callocing for content \n");
	if (line->content)
	{
		printf("t_line_init before memset \n");
		//ft_memset((void*)line->content, '\0', MALLOC_SIZE);
		printf("t_line_init after memset \n");
		return (1);
	}
	return (0);
}
*/

static void	update_buffer_index(t_buffer *lbuffer)
{
	//printf("update_buffer_index start \n");
	lbuffer->eol_index = ft_strat(lbuffer->content, '\n', 1);
}

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
static int	read_next_chunk(t_buffer *lbuffer, int fd)
{
	//printf("read_next_chunk start \n");
	//print_t_buffer(lbuffer);
	ssize_t	bytes_read;

	bytes_read = read(fd, lbuffer->content, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		printf("read_next_chunk.read(): Error Reading\n");
		return (-1);
	}
	else
	{
		lbuffer->len = bytes_read;
	}
	update_buffer_index(lbuffer);
	//printf("lbuffer after read_next_chunk:\n");
	//print_t_buffer(lbuffer);
	return (bytes_read);
}

static int	grow_line(t_line *gline, t_buffer *lbuffer)
{
	// HANDLE multiple \n in a row!
	//printf("grow_line start \n");
	char	*new_alloc;

	if ((gline->len + BUFFER_SIZE) >= gline->bytes_allocated - 1)
	{
		new_alloc = (char *)ft_calloc(sizeof(char), (gline->bytes_allocated + MALLOC_SIZE));
		if (!new_alloc)
			return (-1);
		ft_memmove(new_alloc, gline->content, gline->len);
		free(gline->content);
		gline->content = new_alloc;
		gline->bytes_allocated += MALLOC_SIZE;
	}
	if (lbuffer->eol_index == NO_NEW_LINE)
	{
		ft_memmove((void*)(gline->content + gline->len), (void*)lbuffer->content, lbuffer->len + 1);
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
		lbuffer->len = BUFFER_SIZE - (lbuffer->eol_index + 1);
		ft_memmove((void*)lbuffer->content, ((void*)lbuffer->content + lbuffer->eol_index + 1), lbuffer->len);
		ft_memset((void*)(lbuffer->content + lbuffer->len), '\0', BUFFER_SIZE - lbuffer->len);
		lbuffer->eol_index = ft_strat(lbuffer->content, '\n', 1);
		//update_buffer_index(lbuffer);
	}
	//*(gline->content + gline->len + 1) = '\0';
	//printf("gline after growline:\n");
	//print_t_line(gline);
	return (1);
}

void	*error_exit()
{
	printf("error_exit start \n");
	//free stuff that needs to be freed...
	return (NULL);
}
char	*get_next_line(int fd)
{
	//static char	line_buffer[BUFFER_SIZE];
	static t_buffer	lbuffer;
	t_line			growing_line;
	int				read_result;

	if (BUFFER_SIZE == 0)
		return (NULL);

	read_result = 0;
	//printf("get_next_line start \n");
	//print_t_buffer(&lbuffer);
	growing_line.content = ft_calloc(sizeof(t_line), MALLOC_SIZE);
	growing_line.len = 0;
	growing_line.bytes_allocated = MALLOC_SIZE;
	growing_line.eol_found = 0;
	//lbuffer.eol_index = (size_t) (-1);

	if (!growing_line.content)
		return (error_exit());
	//printf("get_next_line after t_line_init \n");
	if (!lbuffer.len)
		read_next_chunk(&lbuffer, fd);
	while (lbuffer.len && !growing_line.eol_found)
	{
		if (!grow_line(&growing_line, &lbuffer))
			return (error_exit());
		if (!lbuffer.len)
		{
			read_result = read_next_chunk(&lbuffer, fd);
			if (read_result < 0)
				return (error_exit());
			if (read_result == 0)
			{
				printf("End of File");
				return (NULL);
			}
		}

	}
	//print_t_buffer(&lbuffer);
	//print_t_line(&growing_line);
	return (growing_line.content);
}

#include <fcntl.h>
int	main(void)
{
	char	*next_line;
	int		fd1;
	int		i;

	i = 0;
	printf("Main start\n");
	fd1 = open("./input.txt", O_RDONLY);
	printf("File opened: %i\n", fd1);
	//open file and get file descriptor fd
	next_line = get_next_line(fd1);
	while (next_line && i < 100)
	{
		printf("LINE NO %i: %s\n", ++i , next_line);
		free(next_line);
		next_line = get_next_line(fd1);
	}
	if (next_line)
		free(next_line);
	//printf("Reached End of File");

	return (0);
}
