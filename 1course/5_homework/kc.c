#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int R = 10;
int Q = 31;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int get_hash    (const char *start, const char *fin);

int update_hash (int current, int n, char cprev, char cnext);

unsigned long long pow_mod (unsigned n, unsigned k, unsigned m);

int rabin_karp (const char *needle, const char *haystack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int get_hash (const char *start, const char *fin)
{
    char* pointer = (char*) fin;

    int res = 0;
    int i = 0;

    while (pointer != start)
    {
        res += *pointer * (int) pow_mod (R, i, Q);
        res %= Q;

        ++i;
        --pointer;
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int update_hash (int current, int n, char cprev, char cnext)
{
    int res = current - cprev * n;

    res = res * R + cnext;

    res %= Q;

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned long long pow_mod (unsigned n, unsigned k, unsigned m)
{
    unsigned long long mult = n % m;
    unsigned long long prod = 1;

    while (k > 0) 
    {
        if ((k % 2) == 1) 
        {
            prod = (prod * mult) % m; k = k - 1;
        }

        else 
        {
            mult = (mult * mult) % m; k = k / 2;
        }
    }
    
    return prod;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int rabin_karp (const char *needle, const char *haystack) 
{
    unsigned n, target, cur, count = 0, left = 0, right = strlen(needle);

    target = get_hash(needle, needle + right);
    cur = get_hash(haystack, haystack + right);
    n = pow_mod(R, right - 1, Q);

    while(haystack[right] != 0)
    {
        cur = update_hash(cur, n, haystack[left], haystack[right]);

        left += 1;

        if (target == cur)
        {
            int some_res = 1;

            for (int i = left; i <= right; ++i)  //TODO: я хз что, но что-то здесь сломалось
                if (haystack[i] != needle[i - left])
                {
                    some_res = 0;

                    break;
                }

            if (some_res)
                return left;
        }

        right += 1;
    }

    return -1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    char haystack[] = "aufkhdlfndkflexxxxxx";

    char needle[] = "flex";

    printf ("%d\n", get_hash (needle, needle + strlen (needle)));

    int res = rabin_karp (needle, haystack);

    printf ("%d\n%s\n", res, haystack + res);
}