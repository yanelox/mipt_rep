#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	umask(0);

	int fd = open("1.txt", O_WRONLY | O_CREAT, 00700);

	const char str[] = "Hello, world!\n";

	write(fd, str, 14);

	close(fd);

	return 0;
}
