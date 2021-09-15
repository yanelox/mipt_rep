#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <assert.h>
#include <string.h>

int main()
{
	int fd1[2] = {0, 0};
	int fd2[2] = {0, 0};

	pipe (fd1);
	pipe (fd2);

	int id = fork();

	char* str1 = "Hello, parent!";
	char* str2 = "Hello, child1";

	char* buf = calloc (100, sizeof(char));

	if (!id)
	{
		write (fd1[1], str1, strlen(str1));
		read (fd2[0], buf, strlen(str2));

		printf ("Child: my_id = %d\n", getpid());
		printf ("Send message: \"%s\"\n", str1);
		printf ("Get message: \"%s\"\n", buf);
	}

	else
        {
                write (fd2[1], str2, strlen(str2));
                read (fd1[0], buf, strlen(str1));

                printf ("Parent: my_id = %d\n", getpid());
                printf ("Send message: \"%s\"\n", str2);
                printf ("Get message: \"%s\"\n", buf); 
	}

	printf ("-------------------------------\n");

	free (buf);
	close (fd1[0]);
	close (fd1[1]);
	close (fd2[0]);
	close (fd2[1]);
	
	return 0;
}
