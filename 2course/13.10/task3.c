#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main ()
{
    int ftok_id = ftok ("mem_buf.c", 1);
    
    int sem_key = semget (ftok_id, 2, IPC_CREAT | 0666);

    int res, mode;

    struct sembuf cm1 = {0, 1, 0};
    struct sembuf cm2 = {1, 1, 0};

    scanf ("%d", &mode);
    scanf ("%d", &res);

    if (mode == 0)
    {
        printf ("semctl: %d\n", semctl (sem_key, 0, SETVAL, res));
        
        printf ("%d\n", semctl (sem_key, 0, GETVAL));

        semop (sem_key, &cm1, 1);

        printf ("%d\n", semctl (sem_key, 0, GETVAL));
    }

    else if (mode == 1)
    {
        ushort array[2]; 

        array[0] = res;
        array[1] = res;

        printf ("semctl: %d\n", semctl (sem_key, 0, SETALL, array));//TODO: не работает эта строка

        printf ("%d\n", semctl (sem_key, 0, GETVAL));
        printf ("%d\n", semctl (sem_key, 1, GETVAL));

        semop (sem_key, &cm1, 1);
        semop (sem_key, &cm2, 1);

        printf ("%d\n", semctl (sem_key, 0, GETVAL)); 
        printf ("%d\n", semctl (sem_key, 1, GETVAL));   
    }

    return 0;
}