#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct message
{
    long mtype;
    int mtext;
};

int main()
{
    int ftok_id = ftok ("membuf.c", 1);

    int msg_key = msgget (ftok_id, IPC_CREAT | 0666);

    struct message msg;

    msg.mtext = 0;

    while (msg.mtext != 42)
    {
        msgrcv (msg_key, &msg, sizeof(int), 1, 0);
        printf ("%d\n", msg.mtext);
    }
}