#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	umask(0);

	int fd = open ("1.txt", O_RDONLY, 00700);

	char* buf= calloc (20, sizeof(char));

	read (fd, buf, 14);

	printf ("%s", buf);

	free (buf);

	close (fd);
}
