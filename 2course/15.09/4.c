#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <assert.h>

int main()
{
	int fd[2] = {0 , 0};

	int a = pipe (fd);

	assert(a != -1);

	char* str = "Hello, world!";

	int id = fork();

	if (!id)
        {
                write (fd[1], str, 13);
                printf ("Child: my_id = %d\n", getpid());
                printf ("Send message: \"%s\"\n", str);
        }

	else
	{
		char* buf = calloc (20, sizeof(char));

		read (fd[0], buf, 13);

		printf ("Parent: my_id = %d\n", getpid());
		printf ("Get message: \"%s\"\n", buf);
	
		free (buf);
	}

	printf ("--------------------------\n");

	close (fd[0]);
	close (fd[1]);
}
