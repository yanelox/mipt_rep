#include <stdio.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define HUI_PI 3.141592653589793
#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    double a, b;
    double s = 0;

    scanf ("%lf%lf", &a, &b);

    if (2 * b <= a)
        printf ("%.3lf", HUI_PI * b * b);

    else if (b * b <= a * a * 2)
    {
        s = acos (a / (2 * b));
        s = s * b * b - b * a / 2 * sin (s);
        s = HUI_PI * b * b - 4 * s;
        printf ("%.3lf", s);
    }
    
    else
    {
        s = b * b;
        printf ("%.3lf", s);
    }
}