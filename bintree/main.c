#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    Btree_t* res = start_read_zo ("file.txt");

    print_edge (res);

    free_tree (res);
}