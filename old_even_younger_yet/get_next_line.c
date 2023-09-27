
#include "get_next_line.h"

static int	fill_buffer(int	fd, char **buf, ssize_t *sread);
static int	fill_stash(int fd, char **buf, ssize_t *sread, char **stash);
static char	*move_stash_line(char **stash, ssize_t nl_ind);
static int	build_line(char **stash, char **line, ssize_t *sread);

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

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buf;
	ssize_t		sread;
	int			done;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	if (!stash)
	{
		stash = malloc(sizeof(char) * 1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	line = NULL;
	done = 0;
	sread = -2;
	while (!done)
	{
		if (!fill_stash(fd, &buf, &sread, &stash) || sread == -1)
		{
			free(buf);
			return (NULL);
		}
		done = build_line(&stash, &line, &sread);
	}
	if (line == NULL)
		free(stash);
	//if (sread == 0 && stash)
	//	free(stash);
	free(buf);
	return (line);
}
static int	fill_buffer(int	fd, char **buf, ssize_t *sread)
{
	if ((*buf)[0] == '\0')
	{
		*sread = read(fd, *buf, BUFFER_SIZE);
		if (*sread == -1)
			return (0);
		(*buf)[*sread] = '\0';
	}
	return (1);
}
static int	fill_stash(int fd, char **buf, ssize_t *sread, char **stash)
{
	char	*old_stash;
	size_t	stash_len;

	if (*stash != NULL)
	{
		//printf("(*stash)[0]: %d\n", (int)(*stash)[0]);
		//printf("(*stash)[1]: %d\n", (int)(*stash)[1]);
		stash_len = ft_strlen(*stash);
		if (ft_strnat(*stash, '\n', stash_len) != -1)
			return (1);
		if (!fill_buffer(fd, buf, sread))
			return (0);
		if ((*buf)[0] != '\0')
		{
			old_stash = *stash;
			*stash = ft_strjoin(*stash, *buf);
			free(old_stash);
		}
	}
	else
	{
		if (!fill_buffer(fd, buf, sread))
			return (0);
		*stash = ft_strjoin("", *buf);
	}
	if (!*stash)
		return (0);
	(*buf)[0] = '\0';
	return (1);
}
static char	*move_stash_line(char **stash, ssize_t nl_ind)
{
	char	*line;
	size_t	stash_len;

	stash_len = ft_strlen(*stash);
	if (nl_ind < 0 || (nl_ind + 1) == (ssize_t)stash_len)
	{
		line = ft_substr(*stash, 0, stash_len);
		(*stash)[0] = '\0';
	}
	else
	{
		line = ft_substr(*stash, 0, nl_ind + 1);
		ft_strlcpy(*stash, (*stash) + nl_ind + 1, stash_len - nl_ind);
	}
	return (line);
}
static int	build_line(char **stash, char **line, ssize_t *sread)
{
	size_t	stash_len;
	ssize_t	nl_ind;

	if (!*stash)
		return (0);
	stash_len = ft_strlen(*stash);
	if (!stash_len && *sread == 0)
	{
		//free(*stash);
		return (1);
	}
	nl_ind = ft_strnat(*stash, '\n', stash_len);
	if (nl_ind >= 0 || *sread == 0)
	{
		*line = move_stash_line(stash, nl_ind);
		return (1);
	}
	return (0);
}
