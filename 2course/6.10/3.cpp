#include <stdio.h>
#include <pthread.h>

int global_value = 0;

void *func (void *)
{
    printf ("func %lu\n", pthread_self());

    ++global_value;
    printf ("func %d\n", global_value);

    return NULL;
}

void *func1 (void *)
{
    printf ("func1 %lu\n", pthread_self());

    ++global_value;
    printf ("func1 %d\n", global_value);

    return NULL;
}

int main()
{
    pthread_t var = 0, var1 = 0;

    int res = pthread_create (&var, (const pthread_attr_t *) NULL, func, NULL);
    int res1 = pthread_create (&var1, (const pthread_attr_t *) NULL, func1, NULL);

    pthread_join (var, NULL);
    pthread_join (var1, NULL);

    printf ("main %lu %lu %lu\n", pthread_self(), var, var1);

    ++global_value;
    printf ("main %d\n", global_value);
}