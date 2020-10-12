#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <locale.h> 

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum returned_values 
{
    ALL_OK = 42,
    SMTH_WRONG = - 42
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct 
{
    unsigned len;

    char* start;
}
string;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetValues      (char* file_name, unsigned* countStr, unsigned* countSym);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FromFileToStr  (char* file_name, char* str, unsigned len);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FromStrToFile   (string* str, char* file_name, unsigned count);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

string init         (unsigned length, char* start);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FillPMassive    (string* pointers_to_str, char* file_copy, 
                    unsigned countStr, unsigned countSym);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int PrintStr        (char* str, string* str1, unsigned countStr);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrCompare      (const void* s1, const void* s2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int IsLetter        (char a);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrRevCompare   (const void* s1, const void* s2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrQuickSort    (string* mass, unsigned size, 
                    int ( * CompareFunc ) ( const void *, const void * ));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrSwap         (string* s1, string* s2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    setlocale (LC_ALL, "Rus");

    unsigned countStr = 0;
    unsigned countSym = 0;

    char* file_for_sort = "onegin.txt";                 //TODO: сделать названия файлов через параметры main()
    char* sorted_file = "sorted_onegin.txt";

    int checker = GetValues (file_for_sort, &countStr, &countSym);

    assert (checker == ALL_OK);

    char* file_copy = (char*) calloc (countSym + 2, sizeof(char)); 

    assert (file_copy != NULL);                

    checker = FromFileToStr (file_for_sort, file_copy, countSym);

    assert (checker == ALL_OK);

    string pointers_to_str[countStr];

    checker = FillPMassive (pointers_to_str, file_copy, countStr, countSym);

    assert (checker == ALL_OK);

    qsort (pointers_to_str, countStr, sizeof(string), StrRevCompare);

    checker = FromStrToFile (pointers_to_str, sorted_file, countStr);

    assert (checker == ALL_OK);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetValues (char* file_name, unsigned* countStr, unsigned* countSym)
{
    FILE* f = fopen (file_name, "r");

    if (f == NULL)
        return SMTH_WRONG;

    int c = 0, g = 0;

    *countSym = 0;
    *countStr = 0;

    while((c = fgetc (f)) != EOF)
    {
        (*countSym)++;

        if (c == '\n')
            (*countStr)++;

        g = c;
    }

    if (g != '\n')
        (*countStr)++;

    fclose (f);

    return ALL_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FromFileToStr (char* file_name, char* str, unsigned len)
{
    FILE* f = fopen (file_name, "r");

    if (f == NULL or str == NULL or len < 1)
        return SMTH_WRONG;

    unsigned checker = fread (str, sizeof(char), len, f);

    if (checker != len)
        return SMTH_WRONG;

    if ( *(str + len - 1) != '\n')
    {
         *(str + len) = '\n';
         *(str + len + 1) = '\0';
    }

    fclose (f);

    return ALL_OK;
} 

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FromStrToFile (string* str, char* file_name, unsigned countStr)
{
    FILE* f = fopen (file_name, "a");

    if (f == NULL)
        return SMTH_WRONG;

    int checker = fseek (f, 0, SEEK_END);

    if (checker != 0)
        return SMTH_WRONG;

    for (unsigned i = 0; i < countStr; i++)
        for (unsigned j = 0; j < (*(str + i)).len; j++)
            fputc ((int) *((*(str + i)).start + j), f);
    
    fclose (f);

    return ALL_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

string init (unsigned length, char* start)
{
    string str;

    str.len = length;
    str.start = start;

    return str;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FillPMassive (string* pointers_to_str, char* file_copy, unsigned countStr, unsigned countSym)
{
    if (file_copy == NULL)
        return SMTH_WRONG;

    int cur_len = 0, j = 0;
    char* cur_p = file_copy;

    for (int i = 0; i < countStr; i++)
    {
        cur_p = file_copy + j;
        cur_len = 0;

        while(file_copy[j] != '\n' and j < countSym)
        {
            j++;
            cur_len++;
        }

        j++;
        cur_len++;

        pointers_to_str[i] = init (cur_len, cur_p);        
    }

    return ALL_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int PrintStr (char* str, string* str1, unsigned countStr)
{
    if (str == NULL or str1 == NULL)
        return SMTH_WRONG;

    for (unsigned i = 0; i < countStr; i++)
        for (unsigned j = 0; j < (*(str1+i)).len; j++)
            printf ("%c", *((*(str1 + i)).start + j));

    return ALL_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrCompare (const void* s1, const void* s2)
{
    if (s1 == NULL or s2 == NULL)
        return SMTH_WRONG;
 
    string* str1 = (string*) s1;
    string* str2 = (string*) s2;

    if ((*str1).len == 1)
        return 1;
    if ((*str2).len == 1)
        return -1; 

    int i = 0, j = 0;
    char cur_sym1 = '0', cur_sym2 = '0';

    while (i < (*str1).len and j < (*str2).len)
    {
        cur_sym1 = *((*str1).start + i);
        cur_sym2 = *((*str2).start + j);

        if (IsLetter (cur_sym1) and IsLetter (cur_sym2) and cur_sym1 != cur_sym2)
            return (int) cur_sym1 - (int) cur_sym2;
        
        else if (IsLetter (cur_sym1) and !IsLetter (cur_sym2))
            i--;

        else if (!IsLetter (cur_sym1) and IsLetter (cur_sym2))
            j--;
        
        i++;
        j++;
    }

    return (int) (*str1).len - (int) (*str2).len;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int IsLetter (char a)
{
    int x = ('a' <= a <= 'z') or ('A' <= a <= 'Z'); //TODO: Сделать русский язык

    return x;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrRevCompare (const void* s1, const void* s2)  //TODO: починить обратный компаратор
{
    if (s1 == NULL or s2 == NULL)
        return SMTH_WRONG;

    string* str1 = (string*) s1;
    string* str2 = (string*) s2; 

    if ((*str1).len == 1)
        return 1;
    if ((*str2).len == 1)
        return -1; 

    int i = (*str1).len - 1, j = (*str2).len - 1;

    char cur_sym1 = *((*str1).start + i);
    char cur_sym2 = *((*str2).start + j);

    while (!IsLetter (cur_sym1))
    {
        i--;
        cur_sym1 = *((*str1).start + i);
    }

    while (!IsLetter (cur_sym2))
    {
        j--;
        cur_sym2 = *((*str2).start + j);
    }

    while (i >= 0 and j >= 0)
    {
        cur_sym1 = *((*str1).start + i);
        cur_sym2 = *((*str2).start + j);

        if (IsLetter (cur_sym1) and IsLetter (cur_sym2) and cur_sym1 != cur_sym2)
            return (int) cur_sym1 - (int) cur_sym2;

        else if (IsLetter (cur_sym1) and !IsLetter (cur_sym2))
            i++;

        else if (!IsLetter (cur_sym1) and IsLetter (cur_sym2))
            j++;
        
        i--;
        j--;
    }

    return (int) (*str1).len - (int) (*str2).len;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrQuickSort (string* mass, unsigned size, int (* CompareFunc)(const void* el1, const void* el2)) //TODO: пофиксить квиксорт
{
    ;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrSwap (string* s1, string* s2)
{
    if (s1 == NULL or s2 == NULL)
        return SMTH_WRONG;

    string swap_tmp = *s1;
    *s1 = *s2;
    *s2 = swap_tmp;

    return ALL_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//TODO: написать доки
