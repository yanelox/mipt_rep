#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
    int fd = open (argv[1], O_RDWR);

    struct stat statbuf;

    stat (argv[1], &statbuf);

    char* addr = mmap (NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0l);
    
    printf ("%s", addr);

    addr[0] = 'R';

    munmap (addr, statbuf.st_size);
}