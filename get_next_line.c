/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:45:22 by chimpansky        #+#    #+#             */
/*   Updated: 2023/09/16 22:41:28 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* NAME
       read - read from a file descriptor

SYNOPSIS
       #include <unistd.h>

       ssize_t read(int fd, void *buf, size_t count);

DESCRIPTION
       read()  attempts  to  read up to count bytes from file descriptor fd into the buffer starting at
       buf.

       On files that support seeking, the read operation commences at the file  offset,  and  the  file
       offset  is incremented by the number of bytes read.  If the file offset is at or past the end of
       file, no bytes are read, and read() returns zero.

       If count is zero, read() may detect the errors described below.  In the absence of  any  errors,
       or if read() does not check for errors, a read() with a count of 0 returns zero and has no other
       effects.

       According to POSIX.1, if count is greater than SSIZE_MAX, the result is  implementation-defined;
       see NOTES for the upper limit on Linux.

RETURN VALUE
       On  success,  the number of bytes read is returned (zero indicates end of file), and the file position is advanced
       by this number.  It is not an error if this number is smaller than the number of bytes requested; this may  happen
       for  example  because fewer bytes are actually available right now (maybe because we were close to end-of-file, or
       because we are reading from a pipe, or from a terminal), or because read() was interrupted by a signal.  See  also
       NOTES.

       On  error,  -1 is returned, and errno is set appropriately.  In this case, it is left unspecified whether the file
       position (if any) changes.
*/

#include "get_next_line.h"

char    *get_next_line(int fd)
{
	char	line_buffer[3];
	char	*ret_line;
	ssize_t	read_return;

	read_return = read(fd, line_buffer, 3);
	if (read_return == -1)
	{
		printf("Error: get_next_line.read (-1)\n");
		return (NULL);
	}
	if (read_return == 0)
		printf("Reached End of File: get_next_line.read (0)\n");
	printf("get_next_line.read successful: %ld \n", read_return);
	ret_line = malloc(sizeof(char) * (read_return + 1));
	if (!ret_line)
	{
		printf("Error: get_next_line. malloc unsucessful\n");
		return (NULL);
	}
	ft_strlcpy(ret_line, line_buffer, read_return + 1);

	return (ret_line);
}
