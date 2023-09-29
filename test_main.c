#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
int	main(int	argc, char **argv)
{
	//char	*next_line;
	char	*files[26];
	char	*bonus_files[3];
	int		fd1;
	int	input_no;
	int		i;

	files[0] = "test_inputs/input.txt";
	files[1] = "test_inputs/fsoares/empty.txt";
	files[2] = "test_inputs/fsoares/giant_line.txt";
	files[3] = "test_inputs/fsoares/giant_line_nl.txt";
	files[4] = "test_inputs/fsoares/lines_around_10.txt";
	files[5] = "test_inputs/fsoares/1char.txt";
	files[6] = "test_inputs/fsoares/multiple_nl.txt";
	files[7] = "test_inputs/fsoares/one_line_no_nl.txt";
	files[8] = "test_inputs/fsoares/read_error.txt";
	files[9] = "test_inputs/fsoares/variable_nls.txt";
	files[10] = "test_inputs/gnltester/41_no_nl";
	files[11] = "test_inputs/gnltester/41_with_nl";
	files[12] = "test_inputs/gnltester/42_no_nl";
	files[13] = "test_inputs/gnltester/42_with_nl";
	files[14] = "test_inputs/gnltester/43_no_nl";
	files[15] = "test_inputs/gnltester/43_with_nl";
	files[16] = "test_inputs/gnltester/alternate_line_nl_no_nl";
	files[17] = "test_inputs/gnltester/alternate_line_nl_with_nl";
	files[18] = "test_inputs/gnltester/big_line_no_nl";
	files[19] = "test_inputs/gnltester/big_line_with_nl";
	files[20] = "test_inputs/gnltester/empty";
	files[21] = "test_inputs/gnltester/multiple_line_no_nl";
	files[22] = "test_inputs/gnltester/multiple_line_with_nl";
	files[23] = "test_inputs/gnltester/multiple_nlx5";
	files[24] = "test_inputs/gnltester/nl";
	files[25] = "invalid_fd";

	bonus_files[0] = "test_inputs/input1.txt";
	bonus_files[1] = "test_inputs/input2.txt";
	bonus_files[2] = "test_inputs/input3.txt";

	if (argc == 2)
		input_no = atoi(argv[1]);
	else
		input_no = 0;

	i = 0;

	 //Test Mandatory:
	char *next_line;

	fd1 = open(files[input_no], O_RDONLY);
	next_line = get_next_line(fd1);
	while (next_line && i < 10)
	{
		printf("LINE NO %i: ", ++i);
		printf("%s", next_line);
		free(next_line);
		next_line = get_next_line(fd1);
	}

	close(fd1);
	//

/*
	//Test Bonus:
	int		fd2;
	int		fd3;

	fd1 = open(bonus_files[0], O_RDONLY);
	fd2 = open(bonus_files[1], O_RDONLY);
	fd3 = open(bonus_files[2], O_RDONLY);
	char *line;
	line =  get_next_line(fd1);
	printf("%s", line);
	free(line);
	line =  get_next_line(fd2);
	printf("%s", line);
	free(line);
	line =  get_next_line(fd3);
	printf("%s", line);
	free(line);
	line =  get_next_line(27);
	printf("%s", line);
	free(line);
	line =  get_next_line(fd2);
	printf("%s", line);
	free(line);

	close(fd1);
	close(fd2);
	close(fd3);
*/

	return (0);
}
