#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <errno.h>

#define MAX_LEN 1000

struct message_
{
    int status;
    int send_id;
    int rec_id;

    char message[MAX_LEN];
};

int get_text (char* buffer)
{
    char x = 0;

    for (int i = 0; i < MAX_LEN; ++i)
    {
        x = getchar();
        buffer[i] = x;

        if (x == '\n')
        {
            buffer[i + 1] = '\0';
            break; 
        }
    }

    return 0;
}

int writer (struct message_* msg) // 0 - can read, 1 - can write, -1 - bb
{
    char* buffer = (char*) calloc (MAX_LEN, sizeof(char));
    char out_msg[] = "end";
    
    while(msg->status != -1)
    {
        if (msg->status == 1)
        {
            get_text (buffer);
            
            if (!strncmp (out_msg, buffer, 3))
            {
                msg->status = -1;
                break;
            }
            
            strcpy (msg->message, buffer);
            buffer[0] = '\0';

            msg->send_id = getpid();
            msg->status = 0;
        }
    }

    free (buffer);
    return 0;
}

int reader (struct message_* msg)
{
    while (msg->status != -1)
        if (msg->status == 0 && msg->send_id != getppid())
        {
            printf ("From %d:%s", msg->send_id, msg->message);

            msg->status = 1;
        }  

    return 0;
}

int m_init (struct message_* msg)
{
    msg->status = 1;
    msg->rec_id = 0;
    msg->send_id = 0;
    strcpy (msg->message, "NANANA\n");

    return 0;
}

int main ()
{
    int memkey = ftok ("mem_buf1.c", 1);
    
    int shmid = shmget (memkey, sizeof (struct message_), IPC_CREAT | 0666);
    
    struct message_* msg = (struct message_*) shmat (shmid, NULL, 0);
    
    m_init (msg);

    int id = fork();
    
    if (!id)
        reader (msg);
        
    else
        writer (msg);
    
    shmdt (msg);
}