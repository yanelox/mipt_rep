#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stddef.h>
#include <pthread.h>

pthread_t k;
pthread_t m;

void *f1 (void*)
{
    printf ("%lu\n", k);
    return NULL;
}

void *f2(void*)
{
    printf ("%lu\n", m);
    return NULL;
}

int main ()
{
    pthread_create (&k, NULL, f1, NULL);
    pthread_create (&m, NULL, f2, NULL);

	unsigned int key = ftok ("key1.txt", 1);
	int i = shmget(key, 5, 0777|IPC_CREAT|IPC_EXCL);
	printf ("%d\n", i);
    int *array;
	if(i != -1)
	{
        	array = (int*) shmat(i, NULL, 0);
        	array[0] = 0;
        	array[1] = 0;
            array[2] = 0;
            array[3] = 0;
            array[4] = 0;
    } 
    else
    {	
        int i_1 = shmget (key, 2, 0777);
        array = (int*) shmat (i_1, NULL, 0);
        array[0] += 1;
        array[1] += 1;
    }

    for (int i = 0; i < 5; ++i)
        printf ("Thread %d: %d\n", i + 1, array[i]);
	
    shmdt (&i);
	return 0;
}