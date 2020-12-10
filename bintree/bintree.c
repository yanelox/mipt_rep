#include "bintree.h"
#include <assert.h>
#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Btree_t* create_node (int data, Btree_t* left, Btree_t* right)
{
    Btree_t* res = (Btree_t*) calloc (1, sizeof (Btree_t));

    assert (res);

    res->left  = left;
    res->right = right;
    res->data  = data;

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void free_tree (Btree_t* tree)
{
    assert (tree);

    if (tree->left != (Btree_t*) NULL)
        free_tree (tree->left);

    if (tree->right != (Btree_t*) NULL)
        free_tree (tree->right);

    free (tree);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

static void lvl_print_tree (const Btree_t* tree, int lvl)
{
    for (int i = 0; i < lvl; ++i)
        printf (" ");

    printf ("%d\n", tree->data);

    if (tree->left != NULL)
        lvl_print_tree (tree->left, lvl + 1);

    if (tree->right != NULL)
        lvl_print_tree (tree->right, lvl + 1);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void print_tree (const Btree_t* tree)
{
    assert (tree);

    lvl_print_tree (tree, 0);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void print_edge (const Btree_t* tree)
{
    assert (tree);

    if (tree->left != NULL)
    {
        printf ("%d %d ", tree->data, tree->left->data);

        print_edge (tree->left);
    }

    if (tree->right != NULL)
    {
        printf ("%d %d ", tree->data, tree->right->data);

        print_edge (tree->right);
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

static Btree_t* read_tree_zo (FILE* f)
{
    assert (f);

    char sym;

    int f_res = fscanf (f, "%c", &sym);

    assert (f_res == 1);

    Btree_t* res = NULL;

    if (sym == '1')
    {
        res = create_node (1, NULL, NULL);
        res->left  = read_tree_zo (f);
        res->right = read_tree_zo (f);
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Btree_t* start_read_zo (char* file_name)
{
    assert (file_name);

    FILE* f = fopen (file_name, "r");

    assert (f);

    Btree_t* res = read_tree_zo (f);

    fclose (f);

    return res;
}