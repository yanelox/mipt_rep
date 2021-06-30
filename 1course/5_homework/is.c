#include <stdio.h>
#include <limits.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct tree_t 
{
    struct tree_t *left;
    struct tree_t *right;
    int data;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int help_f (struct tree_t *node, int left, int right)
{
    int res = 1;

    if (node->data < left || node->data > right)
        return 0;

    if (node->left != NULL)
        res *= help_f (node->left, left, node->data);

    if (node->right != NULL)
        res *= help_f (node->right, node->data, right);

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int check_is_bst (struct tree_t *top) 
{
    int res = help_f (top, INT_MIN, INT_MAX);

    return res;
}