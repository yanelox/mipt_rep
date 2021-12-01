#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

int main ()
{
    char msg1[] = "Hello, world1!";
    char msg2[] = "Hello, world2!";

    int tcp_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if (tcp_socket == -1)
    {
        perror("");
        return 0;
    }

    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(26565);
    local_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(tcp_socket, (struct sockaddr*) &local_addr, sizeof(local_addr)) == -1)
    {
        perror ("");
        return 0;
    }

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons (27000);
    dest.sin_addr.s_addr = htonl (INADDR_LOOPBACK);

    sendto (tcp_socket, msg1, 14, 0, (struct sockaddr*) &dest, sizeof (dest));
    sendto (tcp_socket, msg2, 14, 0, (struct sockaddr*) &dest, sizeof (dest));
}