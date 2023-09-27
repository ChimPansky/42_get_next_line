#include "get_next_line.h"

int	main(void)
{
	static char	*test;
	static char *strs[1024];
	char	*test2;
	char	buf[1];
	int	fd;
	int ret;

	test2 = "abc";

	fd = open("test_inputs/input.txt", O_RDONLY);
	close(fd);
	ret = read(fd, buf, 0);
	printf("buf: %s\n", buf);
	printf("ret: %i\n", ret);

	ret = read(fd, buf, 1);
	printf("buf: %s\n", buf);
	printf("ret: %i\n", ret);

	printf("&test: %p\n", &test);
	printf("test: %s\n", test);
	printf("&test2: %p\n", &test2);
	printf("test2: %s\n", test2);
	if (!test2)
	{
		printf("test2 is null\n");
	}

	if (!test)
	{
		printf("test is null\n");
		test = malloc(1);
		test[0] = '\0';
		test[1] = '\0';
		printf("test: %s\n", test);
	}
	static t_buffer test3;
	if (!test3.content)
	{
		printf("test3.content is null\n");
	}

	strs[2] = "abc";

	printf("strs[0]: %s\n", strs[0]);
	printf("strs[2]: %s\n", strs[2]);
	if (!strs[0])
		printf("NOT strs[0]");



	strs[0] = malloc(10);
	*strs[0] = 'a';
	strs[0]++;
	*strs[0] = 'a';
	printf("strs[0]: %s\n", strs[0]);
	strs[0] -= 2;
	//free(strs[0]+1);
	return (0);
}
