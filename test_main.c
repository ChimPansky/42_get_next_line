#include "get_next_line.h"

int	main(void)
{

	static char *strs[1024];
	/*
	strs[2] = "abc";

	printf("strs[0]: %s\n", strs[0]);
	printf("strs[2]: %s\n", strs[2]);
	if (!strs[0])
		printf("NOT strs[0]");

	*/

	strs[0] = malloc(10);
	*strs[0] = 'a';
	strs[0]++;
	*strs[0] = 'a';
	printf("strs[0]: %s\n", strs[0]);
	strs[0] -= 2;
	free(strs[0]+1);
	return (0);
}
