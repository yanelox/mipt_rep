#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct t
{
    struct t* left;
    struct t* right;
    int data;
} node;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

node* make_tree (int n, int* p, int* i)
{
    int j = 0;

    node* res = calloc (1, sizeof (node));

    if (n == 0)
    {
        return NULL;
    }

    if (n == 1)
    {
        res->data = p[0];

        return res;
    }

    for (j = 0; j < n; ++j)
        if (p[0] == i[j])
            break;

    res->data = p[0];

    res->left  = make_tree (j, p + 1, i);
    res->right = make_tree (n - j - 1, p + j + 1, i + j + 1);

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int print_tree (node* t)
{
    printf ("%d ", t->data);

    if (t->left != NULL)
        print_tree (t->left);

    if (t->right != NULL)
        print_tree (t->right);

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int print_top (node* t)
{
    printf ("1 ");

    if (t->left != NULL)
        print_top (t->left);

    else
        printf ("0 ");

    if (t->right != NULL)
        print_top (t->right);

    else
        printf ("0 ");

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n;
    int* p = NULL;
    int* i = NULL;
    node* res = NULL;

    scanf ("%d", &n);

    p = calloc (n, sizeof (int));
    i = calloc (n, sizeof (int));

    for (int j = 0; j < n; ++j)
        scanf ("%d", p + j);

    for (int j = 0; j < n; ++j)
        scanf ("%d", i + j);

    res = make_tree (n, p, i);

    print_top (res);

    print_tree (res);

    free (i);
    free (p);
}