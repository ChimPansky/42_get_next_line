#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	char	*next_line;
	int		fd1;
	int		i;

	i = 0;
	printf("Main start\n");
	fd1 = open("./input.txt", O_RDONLY);
	//fd1 = 0;
	printf("File opened: %i\n", fd1);
	//open file and get file descriptor fd
	write(1,"before  gnl\n", 12);
	while ((next_line = get_next_line(fd1)) && i < 50)
	{
		printf("LINE NO %i: %s\n", ++i , next_line);
		free(next_line);
	}
	next_line = get_next_line(fd1);
		printf("LINE NO %i: %s\n", ++i , next_line);

	if (next_line)
		free(next_line);
	//printf("Reached End of File");

	return (0);
}
