#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stddef.h>
#include <arpa/inet.h>
#include <sys/msg.h>

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

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        printf ("Incorrect arguments\n");
        return 0;
    }

    unsigned int client_ip[1024];

    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(26565);
    // server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    struct in_addr addres;

    if (inet_aton (argv[1], &addres) == 0)
    {
        perror("inet_aton");
        return 0;
    }

    server_addr.sin_addr.s_addr = addres.s_addr;

    if(connect(tcp_socket, (const struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) == -1)
    {
        perror ("");
        return 0;
    }

    char message[1024];
    memset (message, '\0', 1024);

    int ret_value = 0;

    int status = 1;

    while (1)
    {
        scanf ("%s", message);

        if (strncmp ("$close", message, 6) == 0)
        {
            close (tcp_socket);
            return 0;
        }

        else if (strncmp ("$get", message, 4) == 0)
        {
            if (status == 0)
            {
                printf ("Remote server broke the connection\n");
                continue;
            }

            int symnum = sendall(tcp_socket, message, 1024, 0);
            if(symnum == -1)
                printf ("Sending error\nn");

            int ret_value = recv (tcp_socket, client_ip, 1024 * sizeof (unsigned int), 0);

            if (ret_value == 0)
            {
                status = 0;
                printf ("Remote server broke the connection\n");
            }

            else if (ret_value == -1)
                printf ("Error on receiving\n");

            else
            {
                for (int i = 1; i < client_ip[0]; ++i)
                    printf ("Client %d have address %u\n", i, client_ip[i]);
            }
        }

        else if (strncmp ("$connect ", message, 9) == 0)
        {
           ;
        }

        else
            printf ("Incorrect command\n");

        memset (message, '\0', 1024);
    }
}   