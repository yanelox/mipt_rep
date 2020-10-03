#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <locale.h> 

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct 
{
    unsigned len;

    char* start;
}
string;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main            ();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void GetValues      (char* file_name, unsigned* countStr, unsigned* countSym);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void FromFileToStr  (char* file_name, char* str, unsigned len);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void FromStrToFile  (string* str, char* file_name, unsigned count);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

string init         (unsigned length, char* start);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void FillPMassive   (string* pointers_to_str, char* file_copy, 
                    unsigned countStr, unsigned countSym);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintStr       (char* str, string* str1, unsigned countStr);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrCompare      (const void* s1, const void* s2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int IsLetter        (char a);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrRevCompare   (const void* s1, const void* s2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StrQuickSort   (string* mass, unsigned size, 
                    int ( * CompareFunc ) ( const void *, const void * ));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StrSwap        (string* s1, string* s2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    
    setlocale(LC_ALL, "Rus");

    unsigned countStr = 0;
    unsigned countSym = 0;

    char* file_for_sort = "onegin.txt";                 //TODO: сделать названия файлов через параметры main()
    char* sorted_file = "sorted_onegin.txt";

    GetValues(file_for_sort, &countStr, &countSym);

    char* file_copy = (char*) calloc (countSym + 2, sizeof(char)); 

    assert (file_copy != NULL);

    FromFileToStr (file_for_sort, file_copy, countSym);

    string pointers_to_str[countStr];

    FillPMassive (pointers_to_str, file_copy, countStr, countSym);

    qsort(pointers_to_str, countStr, sizeof(string), StrRevCompare); 

    //StrQuickSort (pointers_to_str, countStr, StrCompare);

    PrintStr (file_copy, pointers_to_str, countStr);

    FromStrToFile (pointers_to_str, sorted_file, countStr);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void GetValues (char* file_name, unsigned* countStr, unsigned* countSym)
{
    assert (countStr != NULL);
    assert (countSym != NULL);
    assert (countSym != countStr);

    FILE* f = fopen (file_name, "r");

    int c, g;

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
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void FromFileToStr (char* file_name, char* str, unsigned len)
{
    FILE* f = fopen (file_name, "r");

    fread (str, sizeof(char), len, f);

    if ( *(str + len - 1) != '\n')
    {
         *(str + len) = '\n';
         *(str + len + 1) = '\0';
    }

    fclose (f);
} 

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void FromStrToFile (string* str, char* file_name, unsigned countStr)
{
    FILE* f = fopen (file_name, "w");         

    assert (f != NULL);

    for (unsigned i = 0; i < countStr; i++)
        for (unsigned j = 0; j < (*(str + i)).len; j++)
            fputc ((int) *((*(str + i)).start + j), f);
    
    fclose (f);
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

void FillPMassive (string* pointers_to_str, char* file_copy, unsigned countStr, unsigned countSym)
{
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

        pointers_to_str[i] = init(cur_len, cur_p);        
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintStr (char* str, string* str1, unsigned countStr)
{
    for (unsigned i = 0; i < countStr; i++)
        for (unsigned j = 0; j < (*(str1+i)).len; j++)
            printf ("%c", *((*(str1 + i)).start + j));
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrCompare (const void* s1, const void* s2)
{
    string* str1 = (string*) s1;
    string* str2 = (string*) s2; 

    if ((*str1).len == 1)
        return 1;
    else if ((*str2).len == 1)
        return -1; 

    unsigned i = 0, j = 0;
    char cur_sym1 = '0', cur_sym2 = '0';

    while (i < (*str1).len and j < (*str2).len)
    {
        cur_sym1 = *((*str1).start + i);
        cur_sym2 = *((*str2).start + j);

        if (IsLetter(cur_sym1) and IsLetter(cur_sym2) and cur_sym1 != cur_sym2)
            return (int) cur_sym1 - (int) cur_sym2;
        
        else if (IsLetter(cur_sym1) and !IsLetter(cur_sym2))
            i--;

        else if (!IsLetter(cur_sym1) and IsLetter(cur_sym2))
            j--;
        
        i++;
        j++;
    }

    return (int) (*str1).len - (int) (*str2).len;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int IsLetter (char a)
{
    int x = (a >= 'a' and a <= 'z') or (a >= 'A' and a <= 'Z'); //TODO: Сделать русский язык

    return x;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrRevCompare (const void* s1, const void* s2) //TODO: пофиксить баги с обратным компаратором
{
    string* str1 = (string*) s1;
    string* str2 = (string*) s2; 

    if ((*str1).len == 1)
        return 1;
    else if ((*str2).len == 1)
        return -1; 

    unsigned i = (*str1).len - 1, j = (*str2).len - 1;
    char cur_sym1 = '0', cur_sym2 = '0';

    while (i >= 0 and j >= 0)
    {
        cur_sym1 = *((*str1).start + i);    
        cur_sym2 = *((*str2).start + j);

        if (IsLetter(cur_sym1) and IsLetter(cur_sym2) and cur_sym1 != cur_sym2)
            return (int) cur_sym1 - (int) cur_sym2;
        
        else if (IsLetter(cur_sym1) and !IsLetter(cur_sym2))
            i++;

        else if (!IsLetter(cur_sym1) and IsLetter(cur_sym2))
            j++;
        
        i--;
        j--;
    }

    return (int) (*str1).len - (int) (*str2).len;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StrQuickSort (string* mass, unsigned size, int (* CompareFunc)(const void* el1, const void* el2))
{
    unsigned first = 0;
    unsigned second = size - 1;

    string mid_el = mass[size / 2];
    
    while (first < second)
    {
        while ((*CompareFunc) (mass + first, &mid_el) < 0 and first < second)
            first++;

        while ((*CompareFunc) (mass + second, &mid_el) > 0 and first < second)
            second--;

        if (first >= second) 
            break;
        
        else
        {
            StrSwap (mass + first, mass + second);

            first++;
            second--;       
        }
    }

    if (second > 1)
        StrQuickSort (mass, second + 1, CompareFunc);

    if (first + 1 < size and first > 0)
        StrQuickSort (mass + first, size - first, CompareFunc);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StrSwap (string* s1, string* s2)
{
    string swap_tmp = *s1;
    *s1 = *s2;
    *s2 = swap_tmp;
}

//TODO: написать доки
//TODO: написать ассерты