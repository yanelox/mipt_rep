#include <sys/ipc.h>
#include <sys/shm.h>
#include <stddef.h>
#include <stdio.h>


int main()
{
	int shmid;
	scanf ("%d", &shmid);
	shmctl (shmid, IPC_RMID, NULL);
}

