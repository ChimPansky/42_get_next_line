
#include "get_next_line.h"

static int	gnl_init(int fd, t_buffer *stash, t_buffer *buf);
static int	fill_buffer(int	fd, t_buffer *buf, ssize_t *sread);
static int	fill_stash(int fd, t_buffer *buf, ssize_t *sread, t_buffer *stash);
static char	*move_stash_line(t_buffer *stash, ssize_t nl_ind);
static int	build_line(t_buffer *stash, t_buffer *line, ssize_t *sread);


void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
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


///////////////////////////////////////////////////////////777
static int	gnl_init(int fd, t_buffer *stash, t_buffer *buf)
{
	char	tmp[0];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (read(fd, tmp, 0) < 0)
	{
		free_and_null((void**)stash->content);
		return (0);
	}
	buf->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf->content)
	{
		free_and_null((void**)stash->content);
		return (0);
	}
	buf->content[0] = '\0';
	buf->len = 0;
	if (!stash->content)
	{
		stash->content = malloc(sizeof(char) * 1);
		if (!stash->content)
		{
			free_and_null((void**)buf->content);
			return (0);
		}
		stash->content[0] = '\0';
		stash->len = 0;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_buffer	stash;
	t_buffer		line;
	t_buffer		buf;
	ssize_t			sread;
	int				done;

	if (!gnl_init(fd, &stash, &buf))
		return (NULL);
	line.content = NULL;
	done = 0;
	sread = -2;
	while (!done)
	{
		if (!fill_stash(fd, &buf, &sread, &stash) || sread == -1)
			return (NULL);
		done = build_line(&stash, &line, &sread);
	}
	if (line.content == NULL)
		free_and_null((void**)&stash.content);
	free(buf.content);
	return (line.content);
}
static int	fill_buffer(int	fd, t_buffer *buf, ssize_t *sread)
{
	if (buf->content[0] == '\0')
	{
		*sread = read(fd, buf->content, BUFFER_SIZE);
		if (*sread == -1)
			return (0);
		buf->content[*sread] = '\0';
	}
	return (1);
}
static int	fill_stash(int fd, t_buffer *buf, ssize_t *sread, t_buffer *stash)
{
	char	*old_stash;

	if (ft_strnat(stash->content, '\n', stash->len) != -1)
		return (1);
	if (!fill_buffer(fd, buf, sread))
	{
		free_and_null((void**)stash->content);
		return (0);
	}
	if (buf->content[0] != '\0')
	{
		old_stash = stash->content;
		stash->content = ft_strjoin(stash->content, buf->content);
		stash->len = ft_strlen(stash->content);
		free(old_stash);
	}
	if (!stash->content)
	{
		free_and_null((void**)buf->content);
		return (0);
	}
	buf->content[0] = '\0';
	return (1);
}
static char	*move_stash_line(t_buffer *stash, ssize_t nl_ind)
{
	char	*line;

	if (nl_ind < 0 || (nl_ind + 1) == (ssize_t)stash->len)
	{
		line = ft_substr(stash->content, 0, stash->len);
		stash->content[0] = '\0';
		stash->len = 0;
	}
	else
	{
		line = ft_substr(stash->content, 0, nl_ind + 1);
		ft_strlcpy(stash->content, stash->content + nl_ind + 1, stash->len - nl_ind);
		stash->len = ft_strlen(stash->content);
	}
	return (line);
}
static int	build_line(t_buffer *stash, t_buffer *line, ssize_t *sread)
{
	ssize_t	nl_ind;

	if (!stash->content)
		return (0);
	if (!stash->len && *sread == 0)
		return (1);
	nl_ind = ft_strnat(stash->content, '\n', stash->len);
	if (nl_ind >= 0 || *sread == 0)
	{
		line->content = move_stash_line(stash, nl_ind);
		return (1);
	}
	return (0);
}
