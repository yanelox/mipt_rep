#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void JSwap          (const void* el1, const void* el2, size_t el_size);

int IntCmp          (const void* el1, const void* el2);

void QuickSort      (void* p, size_t number, size_t size_el, int (*comparator) (const void*, const void*));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int number = 10;
    int size = 10;
    int max_rand = 100;

    int** a = (int**) calloc (number, sizeof (int*));


    for (int i = 0; i < number; ++i)
        a[i] = (int*) calloc (size, sizeof (int));


    for (int i = 0; i < number; ++i)
        for (int j = 0; j < size; ++j)
            a[i][j] = rand() % max_rand;


    for (int i = 0; i < number; ++i)
    {
        for (int j = 0; j < size; ++j)
            printf ("%d ", a[i][j]);

        printf ("\n");
    }

    printf ("\n");


    for (int i = 0; i < number; ++i)
        QuickSort (a[i], size, sizeof (int), IntCmp);
    

    for (int i = 0; i < number; ++i)
    {
        for (int j = 0; j < size; ++j)
            printf ("%d ", a[i][j]);

        printf ("\n");
    }


    for (int i = 0; i < number; ++i)
        free (a[i]);

    free (a);
}
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void JSwap (const void* el1, const void* el2, size_t el_size)
{
    assert (el1);
    assert (el2);
    assert (el_size > 0);

    char* s1 = (char*) el1;
    char* s2 = (char*) el2;

    char tmp = 0;

    for (unsigned i = 0; i < el_size; ++i)
    {
        tmp = s1[i];
        s1[i] = s2[i];
        s2[i] = tmp;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int IntCmp (const void* el1, const void* el2)
{
    int* s1 = (int*) el1;
    int* s2 = (int*) el2;

    if (*s1 != *s2)
        return (*s1 > *s2) ? 1 : -1;

    else
        return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void QuickSort (void* p, size_t number, size_t size_el, int (*comparator) (const void*, const void*))
{
    char* start = (char*) p;

    int right = number - 1;

    int last = 0;

    int tmp = right / 2;

    if (0 >= right)
        return;

    JSwap (start, start + tmp * size_el, size_el);

    for (int i = 1; i <= right; ++i)
        if (comparator (start + i * size_el, start) < 0)
        {
            ++last;
            JSwap (start + i * size_el, start + last * size_el, size_el);
        }

    JSwap (start + last * size_el, start, size_el);

    QuickSort (start, last, size_el, comparator);
    QuickSort (start + (last + 1) * size_el, number - last - 1, size_el, comparator);
}