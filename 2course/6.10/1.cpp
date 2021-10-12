#include <stdio.h>
#include <pthread.h>

int main()
{
    printf ("%lu\n", pthread_self());
    return 0;
}