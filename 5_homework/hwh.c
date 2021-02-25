#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int a = 929;
int b = 653;
int p_d = 953;
int p_s = 409;
int m = 389;
int r = 73;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct _
{
    struct _* next;

    char* data;

    int count;

} cell;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int pow_mod (int n, int k, int m)
{
    int mult = n % m;
    int prod = 1;

    while (k > 0) 
    {
        if ((k % 2) == 1) 
        {
            prod = (prod * mult) % m; 
            k = k - 1;
        }

        else 
        {
            mult = (mult * mult) % m; 
            k = k / 2;
        }
    }
    
    return prod;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int hash_int (int x)
{
    return ((a * x + b) % p_d) % m;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int hash_str (char* start, int len)
{
    int res = 0;

    for (int i = 1; i <= len; ++i)
    {
        res += start[i - 1] * pow_mod (r, len - i, p_s);

        res = res % p_s;
    }

    return hash_int (res);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int exp_answ = 0;
    int size_text = 0;  
    int s_size_text = 0;
    
    char* text = NULL;
    char* s_text = NULL;
    char* go = NULL;

    cell** table = NULL;

    scanf ("%d%d", &exp_answ, &size_text);

    text = calloc (size_text + 1, sizeof (char));

    scanf ("\n");

    for (int i = 0; i < size_text; ++i)
    {
        scanf ("%c", text + i);
    
        if (text[i] == ' ')
            text[i] = '\0';
    }

    scanf ("\n");
    scanf ("%d", &s_size_text);
    scanf ("\n");

    s_text = calloc (s_size_text, sizeof (char));
    for (int i = 0; i < s_size_text - 1; ++i)
    {
        scanf ("%c", s_text + i);

        if (s_text[i] == ' ')
            s_text[i] = '\0';
    }

    table = calloc (m, sizeof (cell*));
    for (int i = 0; i < m; ++i)
    {
        table[i] = calloc (1, sizeof (cell));
        table[i]->count = -1;
    }

    go = text;

    while (go < text + size_text)
    {
        int hash = hash_str (go, strlen (go));

        cell* tmp_cell = table[hash];

        int status = 0;

        while (!status)
        {
            if (tmp_cell->count == -1)
            {
                tmp_cell->data = go;
                tmp_cell->count = 1;

                tmp_cell->next = calloc (1, sizeof (cell));

                tmp_cell->next->count = -1;
            }

            else if (strlen (tmp_cell->data) == strlen (go))
            {
                for (int i = 0; i < strlen (go); ++i)
                    if (tmp_cell->data[i] != go[i])
                    {
                        status = 1;
                        break;
                    }

                if (!status)
                    ++tmp_cell->count;

                else
                {
                    status = 0;
                    tmp_cell = tmp_cell->next;
                }
            }
        }
    }

    for (int i = 0; i < m; ++i)
        free (table[i]);

    free (table);
    free (text);
    free (s_text);
}