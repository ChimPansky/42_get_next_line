/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:05:59 by tkasbari          #+#    #+#             */
/*   Updated: 2023/09/28 22:40:13 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	gnl_init(int fd, t_buffer *buf, t_buffer *line, int *err)
{
	line->cont = NULL;
	line->len = 0;
	*err = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!buf->cont)
	{
		buf->cont = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf->cont)
			return (0);
		buf->len = 0;
		buf->last_read = -2;
	}
	if ((!buf->len && !buf->last_read))
	{
		free_and_null((void **)buf->cont);
		buf->len = 0;
		return (0);
	}
	return (1);
}

static int	check_and_fill_buf(int fd, t_buffer *buf, int *err)
{
	int	i;

	if (!buf->len)
	{
		buf->last_read = read(fd, buf->cont, BUFFER_SIZE);
		buf->len = buf->last_read;
		if (buf->last_read < 0)
		{
			*err = 1;
			return (-1);
		}
	}
	i = 0;
	while (i < buf->len && buf->cont[i] != '\n')
		i++;
	if (i == buf->len)
		return (-1);
	return (i + 1);
}

static void	move_buf_line(t_buffer *buf, t_buffer *line, int nbytes, int *err)
{
	char	*new;

	new = malloc(sizeof(char *) * (line->len + nbytes + 1));
	if (!new)
	{
		*err = 1;
		return ;
	}
	if (line->cont && line->len > 0)
		ft_memmove(new, line->cont, line->len);
	ft_memmove(new + line->len, buf->cont, nbytes);
	line->len += nbytes;
	new[line->len] = '\0';
	free(line->cont);
	line->cont = new;
	if (nbytes == buf->len)
		buf->len = 0;
	else
	{
		ft_memmove(buf->cont, buf->cont + nbytes, buf->len - nbytes);
		buf->len -= nbytes;
	}
}

static int	create_line(int fd, t_buffer *buf, t_buffer *line, int *err)
{
	int		nbytes;
	char	last;

	nbytes = check_and_fill_buf(fd, buf, err);
	if (*err)
		return (1);
	if (nbytes < 0)
		nbytes = buf->len;
	if (!buf->len && !buf->last_read)
		return (1);
	move_buf_line(buf, line, nbytes, err);
	if (*err)
		return (1);
	last = line->cont[line->len - 1];
	if (last == '\n')
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buffer	buf[MAX_FDS];
	t_buffer		line;
	int				err;

	if (!gnl_init(fd, &buf[fd], &line, &err))
		return (NULL);
	while (!create_line(fd, &buf[fd], &line, &err))
		;
	if (err)
		free_and_null((void **)&line.cont);
	if (!line.cont || err || (!buf[fd].len && !buf[fd].last_read))
	{
		free_and_null((void **)&buf[fd].cont);
		buf[fd].len = 0;
	}
	return (line.cont);
}
