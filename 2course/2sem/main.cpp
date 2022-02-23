#include "task1.h"  

int main ()
{
    math::vector a{1, 2, 3};
    math::matrix b{math::vector {1, 0,0}, {0, 1, 0}, {0, 0, 1}};

    std::cout << (a && a) << "\n";

    return 0;
}