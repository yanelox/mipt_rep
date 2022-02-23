#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/shm.h>

#define MAX_SIZE 512
#define MY_SETVAl 4242
#define MY_GETVAL 9797

struct semawhore
{
    int S[MAX_SIZE];
    int size;
};

int my_ftok (char* str, int n)
{
    return ftok (str, n);
}

int my_sem_get (int memkey, int count, int flag)
{
    assert (count < MAX_SIZE);

    int res = shmget (memkey, sizeof (struct semawhore), flag);

    struct semawhore* tmp = shmat (res, NULL, 0);

    tmp->size = count;

    return res;
}

int my_semop (int sem_key, struct sembuf* m, int n)
{
    assert (m);

    struct semawhore* sem = (struct semawhore*) shmat (sem_key, NULL, 0);

    for (int i = 0; i < n && i < sem->size; ++i)
        if (m[i].sem_op == 0)
            while (sem->S[i] == 0)
                ;

        else if (m[i].sem_op > 0)
            sem->S[i] += m[i].sem_op;

        else
        {
            while (sem->S[i] < - m[i].sem_op)
                ;

            sem->S[i] += m[i].sem_op;
        }

    return 0;
}

int my_semctl (int sem_key, int sem_n, int mode, int val)
{
    struct semawhore* sem = (struct semawhore*) shmat (sem_key, NULL, 0);

    assert (sem_n < sem->size);

    if (mode == MY_SETVAl)
    {
        sem->S[sem_n] = val;
    }

    else if (mode == MY_GETVAL)
    {
        return sem->S[sem_n];
    }

    return 0;
}

int main ()
{
    int ftok_id = my_ftok ("mem_buf.c", 1);

    int sem_key = my_sem_get (ftok_id, 1, IPC_CREAT | 0666);

    struct sembuf cm = {0, -1, 0};

    my_semop (sem_key, &cm, 1);

    printf ("jopa\n");
}