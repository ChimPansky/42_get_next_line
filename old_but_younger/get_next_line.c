
#include "get_next_line.h"

static int	check_line_size(t_line *gline, t_buffer *buf);
static int	grow_line(t_line *gline, t_buffer *buf, int fd);
static int	read_buf(t_buffer *buf, int fd);
static char	*print_buf(t_buffer *buf);
char	*get_next_line(int fd);


static int	check_line_size(t_line *gline, t_buffer *buf)
{
	size_t	addition;
	int		nbytes;
	char	*new;
	if (buf->nl_ind == -1)
		addition = buf->len;
	else
		addition = buf->nl_ind + 1;
	if (gline->len + addition > gline->allocated - 1)
		new = ft_calloc(sizeof(char), gline->allocated + BUFFER_SIZE);
	if (!new)
		return (-1);
	ft_memmove(new, gline->content, gline->len);
	free(gline->content);
	gline->content = new;
	return (0);
}

static int	grow_line(t_line *gline, t_buffer *buf, int fd)
{
	int		nbytes;

	if (!gline->content)
	{
		gline->len = 0;
		gline->eol_ind = -1;
		gline->ready_to_print = 0;
		gline->content = ft_calloc(sizeof(char), 2 * BUFFER_SIZE);
		if (!gline->content)
			return (-1);
		gline->allocated = 2 * BUFFER_SIZE;
	}
	else if (check_line_size(gline, buf) < 0)
		return (-1);
	if (buf->nl_ind > -1)
		nbytes = buf->nl_ind + 1;
	else
		nbytes = buf->len;
	ft_memmove(gline->content + gline->len, buf->content, nbytes);
	gline->len += nbytes;
	ft_memmove(buf->content, (buf->content + nbytes), buf->len - nbytes);
	buf->len -= nbytes;
	ft_memset(buf->content + buf->len, '\0', nbytes);
	buf->nl_ind = ft_strnat(buf->content, '\n', buf->len);
	gline->eol_ind = ft_strnat(gline->content, '\n', gline->len);
	gline->ready_to_print = 1;
	if (gline->eol_ind > -1)
		return (1);
	else
	{
		nbytes = read_buf(buf, fd);
		if (nbytes > 0)
		{
			gline->ready_to_print = 0;
			return (0);
		}
		if (nbytes == 0)
			return (1);
		if (nbytes = -1)
		{
			gline->content = NULL;
			return -1;
		}
	}
}

static int	read_buf(t_buffer *buf, int fd)
{
	int	bytes_read;

	bytes_read = 0;
	if (!buf->len)
	{
		bytes_read = read(fd, buf->content, BUFFER_SIZE);
		buf->len = bytes_read;
		buf->nl_ind = ft_strnat(buf->content, '\n', buf->len);
		if (bytes_read < BUFFER_SIZE)
			buf->ready_to_print = 1;
		else
			buf->ready_to_print = 0;
	}
	if (buf->nl_ind > -1)
		buf->ready_to_print = 1;
	else
		buf->ready_to_print = 0;
	return (bytes_read);
}

static char	*print_buf(t_buffer *buf)
{
	char	*result;
	size_t	nbytes;

	if (buf->nl_ind > -1)
		nbytes = buf->nl_ind + 1;
	else
		nbytes = buf->len;
	result = ft_calloc(sizeof(char), nbytes +1);
	if (!result)
		return (NULL);
	ft_memmove(result, buf->content, nbytes);
	ft_memmove(buf->content, (buf->content + nbytes), buf->len - nbytes);
	buf->len -= nbytes;
	ft_memset(buf->content + buf->len, '\0', nbytes);
	buf->nl_ind = ft_strnat(buf->content, '\n', buf->len);
	if (buf->nl_ind > -1)
		buf->ready_to_print = 1;
	else
		buf->ready_to_print = 0;
	return (result);
}

char	*get_next_line(int fd)
{
	static t_buffer	buf;
	t_line			gline;

	if (read_buf(&buf, fd) == -1)
		return (NULL);
	if (buf.ready_to_print)
	{
		//ft_putstr_fd("ready_to_print!\n", 1);
		//ft_putstr_fd(buf.content, 1);

		//ft_putnbr_fd(buf.len, 1);
		//ft_putstr_fd("\n", 1);
		//ft_putnbr_fd(buf.nl_ind, 1);
		//ft_putstr_fd("\n", 1);
		return (print_buf(&buf));
	}
	while (!grow_line(&gline, &buf, fd)) ;
	if (gline.content == NULL)
		ft_putstr_fd("CONTENT == NULL", 1);
	return (gline.content);
}
