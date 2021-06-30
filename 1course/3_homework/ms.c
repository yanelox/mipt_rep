#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void IntSwap (int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void merge (int* arr, int l, int m, int r)
{
    int second = 0;
    int start = m + 1;
    int tmp = 0;

    for (int j = l; j <= m; ++j)
    {
        for (second = start; second <= r; ++second)
            if (arr[l] < arr[second])
                break;

        --second;

        tmp = arr[l];

        for (int i = l; i < second; ++i)
            arr[i] = arr[i + 1];

        arr[second] = tmp;

        start = second + 1;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int arr[] = {1, 3, 5, 8, 11, 13, 2, 4, 6, 7};

    merge (arr, 0, 5, 9);

    for (int i = 0; i < 10; ++i)
        printf ("%d ", arr[i]);

    printf ("\n");
}