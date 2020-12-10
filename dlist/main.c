#include "dlist.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    d_list* list = DListRead ("file.txt");

    DListPrint (list);

    list = DListReverse (list);

    DListPrint (list);

    DListDtor (list);
}