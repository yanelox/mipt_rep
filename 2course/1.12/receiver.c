#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

int main ()
{
    int tcp_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if (tcp_socket == -1)
    {
        perror("");
        return 0;
    }

    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(27000);
    local_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(tcp_socket, (struct sockaddr*) &local_addr, sizeof(local_addr)) == -1)
    {
        perror ("");
        return 0;
    }

    struct sockaddr_in dest;
    socklen_t len;

    char buffer[1024];
    buffer[1023] = '\0';

    recvfrom (tcp_socket, buffer, 1024, 0, (struct sockaddr*) &dest, &len);
    printf ("%s\n", buffer);

    recvfrom (tcp_socket, buffer, 1024, 0, (struct sockaddr*) &dest, &len);
    printf ("%s\n", buffer);
}