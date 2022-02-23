#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct message
{
    long mtype;
    char mtext[256];
};

int main()
{
    int ftok_id = ftok ("membuf.c", 1);

    int msg_key = msgget (ftok_id, IPC_CREAT | 0666);

    struct message msg;

    msg.mtype = 1;

    scanf("%s", msg.mtext);

    msgsnd (msg_key, &msg, 256, 0);
}