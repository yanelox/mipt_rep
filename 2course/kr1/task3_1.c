#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/shm.h>

#define MAX_SIZE 256

struct msg
{
    char mtext[MAX_SIZE];
    int f;
};

int main ()
{
    int ftok_id = ftok ("mb3.c", 1);

    int key =  shmget (ftok_id, sizeof (struct msg), IPC_CREAT | 0666);

    struct msg* res = shmat (key, NULL, 0);

    while (res->f != 1)
        ;

    res->f = 0;
    // printf ("%s\n", res->mtext);
    system (res->mtext);
}