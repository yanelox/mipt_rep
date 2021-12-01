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
    return (n == -1 ? -1 : total);
}

int main ()
{
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (tcp_socket == -1)
    {
        perror("");
        return 0;
    }

    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(26565);
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(tcp_socket, (struct sockaddr*) &local_addr, sizeof(local_addr)) == -1)
    {
        perror ("");
        return 0;
    }

    if(listen(tcp_socket, 1) == -1)
    {
        perror ("");
        return 0;
    }

    struct sockaddr_in client_addr;
    int client_addrlen;

    int com_socket = accept(tcp_socket,(struct sockaddr *) &client_addr, &client_addrlen);
    
    if(com_socket == -1)
    {
        perror ("");
        return 0;
    }

    char buffer[1024];
    buffer[1023] = '\0';

    int bytes_recv = recv(com_socket, buffer, 1024, 0);
    if(bytes_recv == -1)
    {
        perror ("");
        return 0;
    }

    printf ("%s\n", buffer);

    int symnum = sendall(com_socket, buffer, bytes_recv, 0);
    if(symnum == -1)
    {
        perror ("");
        return 0;
    }

    close (com_socket);
    close (tcp_socket);
}