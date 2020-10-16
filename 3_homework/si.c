#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int moveright (int* arr, int key, int last)
{
    int j;

    for (j = last - 1; arr[j] > key; j--)
        arr[j + 1] = arr[j];

    return j + 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int arr[] = {1, 2, 4, 5, 3, 2};
    int key = 3, last = 4;

    int a = moveright (arr, key, last);

    for (int i = 0; i < 6; i++)
        printf ("%d ", arr[i]);

    printf ("\n%d\n", a);
}