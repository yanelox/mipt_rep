#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int fd[2] = {0, 0};
	
	pipe (fd);

	char* str = "Hello, world!\n";
	char* buf = calloc (20, sizeof(char));
	
	write (fd[1], str, 14);

	read (fd[0], buf, 14);

	printf ("%s", buf);

	free (buf);
	close(fd[1]);
	close(fd[2]);

	return 0;
}
