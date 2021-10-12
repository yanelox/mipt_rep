#include <stdio.h>
#include <pthread.h>

int global_value = 0;

void *func (void *)
{
    printf ("%lu\n", pthread_self());

    ++global_value;
    printf ("%d\n", global_value);

    return NULL;
}

int main()
{
    pthread_t var = 0;

    int res = pthread_create (&var, (const pthread_attr_t *) NULL, func, NULL);

    pthread_join (var, (void**) NULL);

    printf ("%lu %lu\n", pthread_self(), var);

    ++global_value;
    printf ("%d\n", global_value);
}