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

cell** fill_table (char* text, int size_text)
{
    cell** table = NULL;
    char* go = NULL;

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

        // printf ("%d\n", hash);

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

                status = 1;
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
                {
                    ++tmp_cell->count;
                    status = 1;
                }
            }

            tmp_cell = tmp_cell->next;
        }

        go += strlen (go) + 1;
    }

    return table;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char* get_text (int size)
{
    char* text = NULL;

    text = calloc (size + 1, sizeof (char));

    for (int i = 0; i < size; ++i)
    {
        scanf ("%c", text + i);

        if (text[i] == ' ')
            text[i] = '\0';
    }

    return text;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int print_text (char* text, int size)
{
    for (int i = 0; i < size; ++i)
        if (text[i] != '\0')
            printf ("%c", text[i]);
        else
            printf (" ");

    printf ("\n");

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int* find_str (cell** table, int exp_answ, char* s_text, int size)
{
    int* res = calloc (exp_answ, sizeof (int));

    char* go = s_text;

    int hash = 0;

    cell* tmp_cell = NULL;

    for (int i = 0; i < exp_answ; ++i)
    {
        hash = hash_str (go, strlen (go));

        tmp_cell = table[hash];

        while (tmp_cell)
        {
            int status = 1;

            if (tmp_cell->count == -1)
            {
                res[i] = 0;
                tmp_cell = NULL;
            }

            else if (tmp_cell->count != -1)
            {
                if (strlen (tmp_cell->data) == strlen (go))
                {
                    for (int j = 0; j < strlen (go); ++j)
                        if (tmp_cell->data[j] != go[j])
                        {
                            status = 0;
                            break;
                        }
                

                    if(status)
                    {
                        res[i] = tmp_cell->count;
                        tmp_cell = NULL;
                    }

                    else
                        tmp_cell = tmp_cell->next;
                }

                else
                    tmp_cell = tmp_cell->next;
            }
        }

        go += strlen (go) + 1;
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int print_mass (int* mass, int size)
{
    for (int i = 0; i < size; ++i)
        printf ("%d ", mass[i]);

    printf ("\n");

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int exp_answ = 0;
    int size_text = 0;  
    int s_size_text = 0;

    int* answers = NULL;
    
    char* text = NULL;
    char* s_text = NULL;
    char* go = NULL;

    cell** table = NULL;

    scanf ("%d%d", &exp_answ, &size_text);
    scanf ("\n");

    text = get_text (size_text);

    scanf ("\n");
    scanf ("%d", &s_size_text);
    scanf ("\n");

    s_text = get_text (s_size_text);
    
    table = fill_table (text, size_text);

    answers = find_str (table, exp_answ, s_text, s_size_text);

    print_mass (answers, exp_answ);

    for (int i = 0; i < m; ++i)
        free (table[i]);

    free (table);
    free (text);
    free (s_text);
    free (answers);
}