#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct t
{
    struct t* left;
    struct t* right;
    int data;
} node;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int add_el (int el, node* tree)
{
    if (el < tree->data)
    {
        if (tree->left != NULL)
            add_el (el, tree->left);

        else
        {
            tree->left = calloc (1, sizeof (node));

            tree->left->data = el;
        }
    }

    else
    {
        if (tree->right != NULL)
            add_el (el, tree->right);

        else
        {
            tree->right = calloc (1, sizeof (node));

            tree->right->data = el;
        }
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int tree_dest (node* tree)
{
    if (tree->left != NULL)
        tree_dest (tree->left);

    if (tree->right != NULL)
        tree_dest (tree->right);

    free (tree);

    return 0;
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

int print_top (node* t, int* n, int size)
{
    printf ("1 ");

    if (t->left != NULL)
        print_top (t->left, n, size);

    else if (*n < size)
    {
        printf ("0 ");
        ++*n;
    }

    if (t->right != NULL)
        print_top (t->right, n, size);

    else if (*n < size)
    {
        printf ("0 ");
        ++*n;
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n = 0;
    
    int tmp = 0;

    node* res = calloc (1, sizeof (node));

    scanf ("%d", &n);

    scanf ("%d", &tmp);

    res->data = tmp;

    for (int i = 1; i < n; ++i)
    {
        scanf ("%d", &tmp);

        add_el (tmp, res);
    }

    printf ("%d ", n);

    tmp = 0;

    print_top (res, &tmp, n);

    print_tree (res);

    tree_dest (res);
        
    return 0;
}