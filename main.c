#include <stdio.h>
#include "get_next_line_bonus.h"

int main()
{
	int fd;
	int fd2;
	char *arr = NULL;

	fd = open("./text.txt", O_RDONLY);
	fd2 = open("./text2.txt", O_RDONLY);
	if (fd == -1)
		printf("file open error");
		
	printf("\n-----------------------------\n");
	arr = get_next_line(fd);
	printf("%s", arr);
	free(arr);

	printf("\n-----------------------------\n");
	arr = get_next_line(fd);
	printf("%s", arr);
	free(arr);

	printf("\n-----------------------------\n");
	arr = get_next_line(fd2);
	printf("%s", arr);
	free(arr);

	printf("\n-----------------------------\n");
	arr = get_next_line(fd);
	printf("%s", arr);
	free(arr);

	printf("\n-----------------------------\n");
	arr = get_next_line(fd2);
	printf("%s", arr);
	free(arr);

	printf("\n-----------------------------\n");
	arr = get_next_line(fd);
	printf("%s", arr);
	free(arr);	
	close(fd);

	printf("\n-----------------------------\n");
	arr = get_next_line(fd2);
	printf("%s", arr);
	free(arr);

}
