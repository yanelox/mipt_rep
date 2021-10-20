#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stddef.h>
#include <stdio.h>

int main ()
{
	unsigned int key = ftok ("/home/nastya/Documents/key.c", 1);
	int i = shmget(key,1024,0777|IPC_CREAT|IPC_EXCL);
	int *array;
	if(i != -1)
	{
        	array = shmat(i, NULL, 0);
        	array[0] = 1;
        	array[1] = 0;
        	array[2] = 1;
    	} 
    	else
    	{	
        	int i_1 = shmget (key, 1024, 0777);
        	array = shmat (i_1, NULL, 0);
        	array[0] += 1;
        	array[2] += 1;
    	}
    	printf("Program 1: %d times, program 2: %d times, total: %d times\n",array[0],
    	array[1], array[2]);
	shmdt (&i);
	return 0;
}

