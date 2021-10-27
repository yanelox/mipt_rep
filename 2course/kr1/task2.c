#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/shm.h>

struct msg
{
    int n;
};

int main ()
{
    int ftok_id = ftok ("mb2.c", 1);

    int key =  shmget (ftok_id, sizeof (struct msg), IPC_CREAT | 0666);

    struct msg* res = shmat (key, NULL, 0);

    if (res->n % 5 == 0)
        printf ("Hello, world! (%d)\n", res->n);
    
    ++res->n;
}