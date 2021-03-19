#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct dl
{
    struct dl* next;
    struct dl* prev;

    int data;
};

typedef struct dl d_list;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

d_list* DListCtor (int data)
{
    d_list* res = (d_list*) calloc (1, sizeof (d_list));

    res->data = data;

    return res;
}
//ugu
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void DListDtor (d_list* list)
{
    assert (list);

    d_list* tmp = list;

    while (list)
    {
        tmp = list;

        list = list->next;

        free (tmp);
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void DListPrint (d_list* list)
{
    assert (list);

    while (list)
    {
        printf ("%d\n", list->data);

        list = list->next;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

d_list* DListRead (char* file_name)
{
    assert (file_name);

    FILE* f = fopen (file_name, "r");

    d_list* res = NULL;
    d_list** cur = &res;
    d_list* prev = NULL;

    int input = 0;

    while (EOF != fscanf (f, "%d", &input))
    {
        (*cur) = DListCtor (input);
        (*cur)->prev = prev;

        prev = *cur;
        cur = &((*cur)->next);
    }

    fclose (f);

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

d_list* DListReverse

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    d_list* list = DListRead ("test.txt");

    DListPrint (list);

    DListDtor (list);
}