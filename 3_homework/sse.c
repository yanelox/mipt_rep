#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int SortSwap (int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int SelectionSort (int* arr, int cur, int n)
{
    int k = cur;
    int min = arr[cur];

    for (int i = cur; i < n; i++)
        if (arr[i] < min)
        {
            min = arr[i];
            k = i;
        }
    
    SortSwap (arr + cur, arr + k);
    
    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n = 0;
    int* arr = NULL;
    int pos = 0;

    scanf ("%d", &n);

    arr = calloc (n ,sizeof(int));

    for (int i = 0; i < n; i++)
        scanf ("%d", arr + i);

    scanf ("%d", &pos);

    SelectionSort (arr, pos, n);

    for (int i = 0; i < n; i++)
        printf ("%d ", arr[i]);
}