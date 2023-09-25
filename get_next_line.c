
char	*fill_line(char **buf, int fd)
{
	char	*line;
	char	*buf_start;
	char	*buf_nl;
	char	*new;
	int		done;

	done = 0;
	line = ft_calloc(1,1);
	if (!line)
		return (NULL);
	buf_start = buf[fd];
	while (!done)
	{
		buf_nl = ft_strchr(buf[fd], '\n');
		if (buf_nl)
		{
			done = 1;
			new = ft_strjoin(line, ft_substr(buf[fd], 0, buf_nl - buf[fd] + 1));
			if (!new)
				return (NULL);
			free(line);
			line = new;
			buf[fd] = buf_nl + 1;
		}
		ELSE
			READ INTO BUFFER...

	}
	return (line);
}

char	*get_next_line(int fd);
{
	static char *buf[1024];
	char	*line;
	ssize_t	bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (null);
	line = "";
	if (!buf[fd])
		buf[fd] = line;
	if (buf[fd] != "")
	{
		bytes_read = read(fd, buf[fd], BUFFER_SIZE);
		buf[fd][bytes_read] = '\0';
	}
	if (bytes_read < 0)
		return (NULL);
	if (bytes_read == 0)
		return (line);
	line = fill_line(buff, fd);

	return (line);
}
