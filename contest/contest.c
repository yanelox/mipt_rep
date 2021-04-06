#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct dagnode_t 
{
  int nodeid;
  int nchilds;
  int userinfo;
  struct dagnode_t **childs;
};

struct schedarray_t 
{
  int ndevices;
  int *devicesizes;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int c_func (struct dagnode_t* node)
{
    int max = 0;
    int tmp = 0;

    if (node->nchilds == 0)
    {
        node->userinfo = 1;
        return 1;
    }

    for (int i = 0; i < node->nchilds; ++i)
        if ((tmp = c_func (node->childs[i])) > max)
            max = tmp;

    node->userinfo = max + 1;

    return max + 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int do_func (struct dagnode_t* node, int* m)
{   
    if (node->userinfo != -1)
    {
        ++m[node->userinfo - 1];
        node->userinfo = -1;
    } 

    for (int i = 0; i < node->nchilds; ++i)
        do_func (node->childs[i], m);

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct schedarray_t task_schedule (struct dagnode_t **topnodes, int ntopnodes) 
{
    struct schedarray_t res;
    int max = 0;
    int tmp = 0;

    for (int i = 0; i < ntopnodes; ++i)
        if ((tmp = c_func (topnodes[i])) > max)
            max = tmp;

    res.ndevices = max;
    res.devicesizes = calloc (sizeof (int), res.ndevices);

    for (int i = 0; i < ntopnodes; ++i)
        do_func (topnodes[i], res.devicesizes);

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    struct dagnode_t* test = calloc (sizeof (struct dagnode_t), 6);
    struct dagnode_t** X = calloc (sizeof (struct dagnode_t*), 2);
    struct schedarray_t ans;

    for (int i = 0; i < 5; ++i)
        test[i].nodeid = i + 1;


    test[0].nchilds = 2;
    test[1].nchilds = 2;
    test[2].nchilds = 1;

    test[0].childs = calloc (sizeof (struct dagnode_t), 2);
    test[1].childs = calloc (sizeof (struct dagnode_t), 2);
    test[2].childs = calloc (sizeof (struct dagnode_t), 1);

    test[0].childs[0] = &test[4];
    test[0].childs[1] = &test[2];

    test[1].childs[0] = &test[2];
    test[1].childs[1] = &test[3];

    test[2].childs[0] = &test[5];

    for (int i = 0; i < 2; ++i)
        X[i] = &test[i];

    ans = task_schedule (X, 2);

    for (int i = 0; i < ans.ndevices; ++i)
        printf ("%d\n", ans.devicesizes[i]);

    free (test[0].childs);
    free (test[1].childs);
    free (test[2].childs);
    free (X);
    free (test);
    free (ans.devicesizes);
}