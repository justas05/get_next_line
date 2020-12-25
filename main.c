#include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("test_file", O_RDONLY);
	char *line = NULL;

	while (get_next_line(0, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}

	close(fd);

	return 0;
}