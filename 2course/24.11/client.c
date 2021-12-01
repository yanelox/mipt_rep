#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

int sendall(int s, char *buf, int len, int flags)
{
    int total = 0;
    int n;

    while (total < len)
    {
        n = send(s, buf+total, len - total, flags);
        if(n == -1)
        {
            printf("Send error.\n");
            break;
        }
        total += n;
    }
    return(n == -1 ? -1 : total);
}

int main ()
{
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(26565);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(tcp_socket, (const struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) == -1)
    {
        perror ("");
        return 0;
    }

    char message[1024];
    char buffer[1024];
    buffer[1023] = '\0';

    scanf ("%s", message);

    int symnum = sendall(tcp_socket, message, sizeof(message), 0);
    if(symnum == -1)
    {
        perror ("");
        return 0;
    }

    recv(tcp_socket, buffer, sizeof(message), 0);

    printf("%s\n", buffer);
}   