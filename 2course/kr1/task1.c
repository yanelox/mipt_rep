#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>

struct message
{
    long mtype;
    char mtext[256];
};

int main (int argc, char* argv[])
{
    int n = atoi (argv[1]);

    int i = 0;

    int pid = 0;

    for (; i < n - 1; ++i)
        if (pid == 0)
        {
            pid = fork();

            if (pid != 0)
                break;
        }

    int ftok_id = ftok ("mb1.c", 1);

    int msg_key = msgget (ftok_id, IPC_CREAT | 0666);

    struct message msg;

    msg.mtype = 1;

    if (i == 0)
    {   
        for (int j = 1; j < n; ++j)
        {
            msg.mtype = j;

            sprintf (msg.mtext, "Hello %d!\n", j);
            

            msgsnd (msg_key, &msg, 256, 0);
        }

        for (int j = 1; j < n; ++j)
        {
            msgrcv (msg_key, &msg, 256, n + 1, 0);   
        }
    }
    
    else
    {
        msgrcv (msg_key, &msg, 256, i, 0);

        printf ("Proccess number %d receive message: %s", i, msg.mtext);

        msg.mtype = n + 1;

        msgsnd (msg_key, &msg, 256, 0);  
    }

    return 0;
}