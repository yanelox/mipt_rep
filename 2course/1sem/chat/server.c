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

struct server_info
{
    struct sockaddr_in client_addr[1024];
    int client_addrlen[1024];
    int com_socket[1024];
    int number;
    int fid[1024];
    int fid1[1024];
};

struct message 
{
    long mtype;

    char mtext[2048];
};

int sendall(int s, char *buf, int len, int flags)
{
    int total = 0;
    int n;
    
    while (total < len)
    {
        n = send(s, buf+total, len - total, flags);
        if(n == -1)
        {
            perror ("sendall");
            printf ("File descriptor %d\n", s);
            break;
        }
        total += n;
    }

    return (n == -1 ? -1 : total);
}

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        printf ("Incorrect arguments\n");
        return 0;
    }

    int ftok_message_id = ftok ("server.c", 1);
    int msg_key = msgget (ftok_message_id, IPC_CREAT | 0666);

    struct message msg;
    size_t msize = sizeof (struct message) - sizeof (long);

    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (tcp_socket == -1)
    {
        perror("socket");
        return 0;
    }

    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(26565);
    // local_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    struct in_addr addres;

    if (inet_aton (argv[1], &addres) == 0)
    {
        perror("inet_aton");
        return 0;
    }

    // printf ("%X\n", addres.s_addr);
    local_addr.sin_addr.s_addr = addres.s_addr;

    if (bind(tcp_socket, (struct sockaddr*) &local_addr, sizeof(local_addr)) == -1)
    {
        perror ("bind");
        return 0;
    }

    if(listen(tcp_socket, 1) == -1)
    {
        perror ("listen");
        return 0;
    }

    system ("touch server_info.inf");
    unsigned int shm_key = ftok ("server_info.inf", 1);
    
    int shm_index = shmget (shm_key, sizeof (struct server_info), 0777|IPC_CREAT);
    
    struct server_info *info = shmat (shm_index, NULL, 0);

    info->number = 1;

    int fid1 = fork ();
    int cfid = -1;
    int cur_number = 1;
    
    if (fid1 == 0)
        while (1)
        {
            info->com_socket[info->number] = accept(tcp_socket,(struct sockaddr *) info->client_addr + info->number, info->client_addrlen + info->number);
            
            if(info->com_socket[info->number] == -1)
            {
                perror ("accept");
                printf ("Error connecting process\n");
                continue;
            }

            else
            {
                printf ("Succesfully connected client %d. socket: %d\n", info->number, info->com_socket[info->number]);
                // printf ("%d\n", info->number);
                
                cur_number = info->number;
                
                cfid = fork ();

                if (cfid == 0)
                    break;

                else if (cfid != -1)
                {
                    info->fid[info->number] = cfid;
                }

                cfid = -1;
            }

            ++info->number;
        }

    else
    {
        char s[1024];
        memset (s, '\0', 1024);
    
        while (strncmp ("$close", s, 6))
        {
            memset (s, '\0', 1024);
            scanf ("%s", s);
        }

        kill (fid1, SIGKILL);
        for (int i = 1; i < info->number; ++i)
        {
            kill (info->fid[i], SIGKILL);
            kill (info->fid1[i], SIGKILL);
        }

        printf ("Support process killed\n");

        close (tcp_socket);
        for (int i = 1; i < info->number; ++i)
            close (info->com_socket[i]);

        printf ("All sockets are closed\n");
    }

    if (cfid == 0)
    {
        char buffer[1024];
        char send_buffer[2048];
        
        memset (send_buffer, '\0', 2048);

        int ret_value = 0;
        int tmp = 0;

        int client_fid = fork ();

        if (client_fid)
        {
            info->fid1[cur_number] = client_fid;

            while (1)
            {
                memset (buffer, '\0', 1024);

                ret_value = recv (info->com_socket[cur_number], buffer, 1024, 0);

                if (ret_value != -1 && ret_value != 0)
                {
                    sprintf (send_buffer, "Message from client %d: \"%s\"\n", cur_number, buffer);
                    printf ("%s", send_buffer);

                    strncpy (msg.mtext, send_buffer, 2048);

                    for (int i = 1; i < info->number; ++i)
                        if (i != cur_number)
                        {
                            msg.mtype = i;

                            msgsnd (msg_key, &msg, msize, 0);
                        }

                    memset (send_buffer, '\0', 2048);
                }

                else if (ret_value != 0)
                {
                    perror ("recv");
                    printf ("Socket is %d, client number is %d\n", info->com_socket[cur_number], cur_number);
                }

                else
                {
                    printf ("Client %d is disconnected\n", cur_number);
                    break;
                }
            }
        }

        else
        {
            while (1)
            {
                msgrcv (msg_key, &msg, msize, cur_number, 0);

                sendall (info->com_socket[cur_number], msg.mtext, 2048, 0);
            }
        }
    }
}