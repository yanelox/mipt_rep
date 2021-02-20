#include "akinator.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char* argv[])
{
    ak_exit_code = 0;

    if (argc != 3)
    {
        printf ("Incorrect arguments\n");
        return 0;
    }

    TreeEl* tree = StartReading (argv[1]);

    StartGame (tree);

    SaveGraph (*tree, argv[2]);

    StartSaving (*tree, argv[1]);

    TreeDtor (tree);
}