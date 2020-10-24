typedef int (*cmp_t)(void const* lhs, void const* rhs);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int swapss (void* a, void* b, int eltsize)
{
    char tmp;

    char* tmp_a = (char*) a;
    char* tmp_b = (char*) b;

    for (int i = 0; i < eltsize; i++)
    {
        tmp = tmp_a[i];

        tmp_a[i] = tmp_b[i];

        tmp_b[i] = tmp;
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int selstep(void * parr, int eltsize, int numelts, int nsorted, cmp_t cmp) 
{
    void* first = (void*) ((char*) parr + nsorted * eltsize);
    void const* p_min = (void const*) ((char*) parr + nsorted * eltsize);
    void const* tmp;

    for (int i = nsorted; i < numelts; i++)
    {
        tmp = (void const*) ((char*) parr + i * eltsize);

        if (cmp (tmp, p_min))
            p_min = tmp;
    }  

    swapss (first, (void*) p_min, eltsize);

    return 0;
}
