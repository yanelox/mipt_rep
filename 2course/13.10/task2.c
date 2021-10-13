#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main ()
{
    int ftok_id = ftok ("mem_buf.c", 1);
    
    int sem_key = semget (ftok_id, 1, IPC_CREAT | 0666);

    struct sembuf cm = {0, 1, 0};

    printf ("%d\n", semctl (sem_key, 0, GETVAL));

    semop (sem_key, &cm, 1);

    printf ("%d\n", semctl (sem_key, 0, GETVAL));
}