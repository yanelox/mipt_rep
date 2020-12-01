#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "diff.h"
#include "special_onegin.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    char* save     = (char*) "save.txt";
    char* tex_save = (char*) "tex_save.txt";

    int count_sym = CountSymbols (save);

    char* save_copy = (char*) calloc (count_sym, sizeof (char));

    FromFileToStr (save, save_copy, count_sym);

    TreeEl* tree = StartReading (save_copy);

    PrintTree (tree);

    TreeEl* diff_tree = DiffTree (tree, (TreeEl*) NULL);

    PrintTree (diff_tree);

    free (save_copy);

    TreeDtor (tree);

    TreeDtor (diff_tree);
}