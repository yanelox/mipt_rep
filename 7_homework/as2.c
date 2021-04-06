#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int read ()
{
    int number = -1;

    int res = scanf ("%d", number);

    if (res == 0 or res == -1)
        return -2;

    if (number / 128 == 0)
    {
        printf ("MOVI %d\n", number);
    }

    else
    {
        switch (number / 16)
        {
            case 0b1000:
                printf ("ADD %c, %c\n", (number / 4) % 4 + 'A', number % 4 + 'A');
                break;

            case 0b1001:
                printf ("SUB %c, %c\n", (number / 4) % 4 + 'A', number % 4 + 'A');
                break;
            
            case 0b1010:
                printf ("MUL %c, %c\n", (number / 4) % 4 + 'A', number % 4 + 'A');
                break;

            case 0b1011:
                printf ("DIV %c, %c\n", (number / 4) % 4 + 'A', number % 4 + 'A');
                break;

            case 0b1100:
                if (number )

            default:
                break;
        }
    }
}