#include "get_next_line.h"
#include <fcntl.h>

int	main(int	argc, char **argv)
{
	char	*next_line;
	char	*files[26];
	int		fd1;
	int	input_no;
	int		i;

	files[0] = "../test_inputs/fsoares/input.txt";
	files[1] = "../test_inputs/fsoares/empty.txt";
	files[2] = "../test_inputs/fsoares/giant_line.txt";
	files[3] = "../test_inputs/fsoares/giant_line_nl.txt";
	files[4] = "../test_inputs/fsoares/lines_around_10.txt";
	files[5] = "../test_inputs/fsoares/1char.txt";
	files[6] = "../test_inputs/fsoares/multiple_nl.txt";
	files[7] = "../test_inputs/fsoares/one_line_no_nl.txt";
	files[8] = "../test_inputs/fsoares/read_error.txt";
	files[9] = "../test_inputs/fsoares/variable_nls.txt";
	files[10] = "../test_inputs/gnltester/41_no_nl";
	files[11] = "../test_inputs/gnltester/41_with_nl";
	files[12] = "../test_inputs/gnltester/42_no_nl";
	files[13] = "../test_inputs/gnltester/42_with_nl";
	files[14] = "../test_inputs/gnltester/43_no_nl";
	files[15] = "../test_inputs/gnltester/43_with_nl";
	files[16] = "../test_inputs/gnltester/alternate_line_nl_no_nl";
	files[17] = "../test_inputs/gnltester/alternate_line_nl_with_nl";
	files[18] = "../test_inputs/gnltester/big_line_no_nl";
	files[19] = "../test_inputs/gnltester/big_line_with_nl";
	files[20] = "../test_inputs/gnltester/empty";
	files[21] = "../test_inputs/gnltester/multiple_line_no_nl";
	files[22] = "../test_inputs/gnltester/multiple_line_with_nl";
	files[23] = "../test_inputs/gnltester/multiple_nlx5";
	files[24] = "../test_inputs/gnltester/nl";



	if (argc == 2)
		input_no = atoi(argv[1]);
	else
		input_no = 0;


	i = 0;
	//printf("Main start\n");
	fd1 = 0;
	fd1 = open(files[input_no], O_RDONLY);
	//fd1 = open("./input.txt", O_RDONLY);
	//fd1 = 0;
	printf("File opened: %i\n", fd1);
	//open file and get file descriptor fd
	printf("Testinput: %s\n", files[input_no]);
	next_line = NULL;
	while ((next_line = get_next_line(fd1)))
	{
		//printf("XXXXXXXXXXXXXXXXXXXXX\n");
		printf("LINE NO: %i\n", ++i);
		printf("%s", next_line);
		i++;
		free(next_line);
	}
	//next_line = get_next_line(fd1);
	//	printf("LINE NO %i: %s\n", ++i , next_line);

	if (next_line)
		free(next_line);
	//printf("Reached End of File");

	return (0);
}
