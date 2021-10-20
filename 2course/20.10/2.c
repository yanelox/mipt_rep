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

    msg.mtype = 1;
    msg.mtext = 0;

    int x = 0;

    while (x != 42)
    {
        scanf ("%d", &x);

        msg.mtext = x;

        msgsnd (msg_key, &msg, sizeof(int), 0);
    }
}