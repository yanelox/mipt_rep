#include <stdio.h>
#include <xmmintrin.h>

union r
{
    float f;
    __m128 v;
};


int main ()
{
    union r a;
    union r res;

    scanf("%f", &a.f);

    res.v = _mm_rsqrt_ss(a.v);

    // __asm("rsqrtss %0, %1" : "=x" (res.f) : "x" (a.f));

    printf("%f\n", res.f);
}