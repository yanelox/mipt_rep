#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "diff.h"
#include "special_onegin.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char* argv[])
{
    assert (argc == 3);

    char* save     = argv[1];
    char* tex_save = argv[2];

    int count_sym = CountSymbols (save);

    char* save_copy = (char*) calloc (count_sym, sizeof (char));
    FromFileToStr (save, save_copy, count_sym);

    TreeEl* tree = GetG (save_copy);
    PrintTree (tree);
    tree = TreeSimplification (tree, (TreeEl*) NULL);
    PrintTree (tree);

    printf ("//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

    TreeEl* diff_tree = DiffTree (tree, (TreeEl*) NULL);
    PrintTree (diff_tree);
    diff_tree = TreeSimplification (diff_tree, (TreeEl*) NULL);
    PrintTree (diff_tree);

    MakeLFile (tree, diff_tree, tex_save);

    free (save_copy);
    TreeDtor (tree);
    TreeDtor (diff_tree);
}