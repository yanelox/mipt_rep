#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int P (int sem_key)
{
    struct sembuf cm = {0, -1, 0};

    semop (sem_key, &cm, 1);

    return 0;
}

int V (int sem_key)
{
    struct sembuf cm = {0, 1, 0};

    semop (sem_key, &cm, 1);

    return 0;
}

int main ()
{
    int ftok_id = ftok ("mem_buf.c", 1);
    
    int sem_key = semget (ftok_id, 1, IPC_CREAT | 0666);

    int res;

    scanf ("%d", &res);

    V (sem_key);
}