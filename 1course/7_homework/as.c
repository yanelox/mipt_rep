#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int code_f (char* reg, int com)
{
    char a, b;

    a = reg[0];
    b = reg[2];

    // printf ("--\n%x %d %d\n--\n", com , a - 'A', b - 'A');

    if (com >= 0b1000 and com <= 0b1011)
    {
        if (a >= 'A' and a <= 'D' and b >= 'A' and b <= 'D')
            return com * 16 + (a - 'A') * 4 + (b - 'A');

        else
            return -1;
    }

    else if (com == 0b110000 or com == 0b110001)
    {
        if (a >= 'A' and a <= 'D')
            return com * 4 + (a - 'A');

        else
            return -1;
    }

    else
        return -1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int command_code (char* com)
{
    if (com[0] == 'M' and com[1] == 'O' and com[2] == 'V' and com[3] == 'I')
        return 0;

    else if (com[0] == 'A' and com[1] == 'D' and com[2] == 'D')
        return 0b1000;

    else if (com[0] == 'S' and com[1] == 'U' and com[2] == 'B')
        return 0b1001;

    else if (com[0] == 'M' and com[1] == 'U' and com[2] == 'L')
        return 0b1010;

    else if (com[0] == 'D' and com[1] == 'I' and com[2] == 'V')
        return 0b1011;

    else if (com[0] == 'I' and com[1] == 'N')
        return 0b110000;

    else if (com[0] == 'O' and com[1] == 'U' and com[2] == 'T')
        return 0b110001;

    else
        return -1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int read ()
{
    char* input_c = calloc (64, sizeof(char));
    char* input_reg1 = calloc (64, sizeof(char));
    char* input_reg2 = calloc (64, sizeof(char));

    int number = -1;

    int res = scanf ("%s", input_c);

    int code = -1;

    // printf ("%s\n", input_c);

    if (res == -1 or res == 0)
        return -2;

    else
        code = command_code (input_c);

    // printf ("0x%x\n", code);

    if (code == -1)
        return -1;

    else if (code == 0)
        res = scanf ("%d", &number);

    else if (code >= 0b1000 and code <= 0b1011)
    {
        res = scanf ("%s", input_reg1);
        res *= scanf ("%s", input_reg2);
    }
    
    else
    {
        res = scanf ("%s", input_reg1);
    }

    strcat (input_reg1, input_reg2);

    // printf ("%s\n--\n", input_reg1);

    if (res == 0)
        return -1;

    else if (code == 0)
        return number;

    else
        return code_f (input_reg1, code);

    return code;

    free (input_c);
    free (input_reg1);
    free (input_reg2);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int* mass = calloc (1, sizeof(int));

    int res = 0;

    int size = 1;

    for (int i = 0; (res = read ()) != -2; ++i)
    {
        mass[i] = res;

        ++size;

        mass = realloc (mass, size * sizeof (int));
    }

    // printf ("-----\n");
    
    for (int i = 0; i < size - 1; ++i)
        if (mass[i] != -1)
            printf ("0x%x ", mass[i]);
        else
        {
            printf ("ERROR ");
            break;
        }

    printf ("\n");

    free (mass);
}