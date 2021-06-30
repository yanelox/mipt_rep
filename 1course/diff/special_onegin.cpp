#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <locale.h> 
#include "special_onegin.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int onegin_exit_code = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

long int CountSymbols (char* file_name)
{
    assert (file_name != NULL);

    long int count_sym;

    FILE* f = fopen (file_name, "r");

    if (f == NULL)
    {
        onegin_exit_code = CountSymbols_CODE + ONEGIN_FILE_OPEN_ERROR;
        return -1;
    }

    fseek (f, 0, SEEK_END);

    count_sym = ftell (f);

    fseek (f, 0, SEEK_SET);

    count_sym -= ftell (f);

    if (fclose (f) != 0)
    {
        onegin_exit_code = CountSymbols_CODE + ONEGIN_FILE_CLOSE_ERROR;
        return -1;
    }

    return count_sym + 2;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

long int CountStr (char* string_name)
{
    assert (string_name != NULL);

    char c = string_name[0];
    char g = c;
    long int res = 0;

    for (int i = 0; (c = string_name[i]); ++i)
    {
        if (c == '\n')
            ++res;
    
        g = c;
    }

    if (g != '\n')
        ++res;

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FromFileToStr (char* file_name, char* str, unsigned len)
{
    assert (file_name != NULL);
    assert (str != NULL);

    FILE* f = fopen (file_name, "r");

    if (f == NULL)
    {
        onegin_exit_code = FromFileToStr_CODE + ONEGIN_FILE_OPEN_ERROR;
        return -1;
    }

    unsigned checker = fread (str, sizeof(char), len, f);

    if (checker != len - 2)
    {
        onegin_exit_code = FromFileToStr_CODE + ONEGIN_FREAD_ERROR;
        return -1;
    }

    if ( *(str + len - 3) != '\n')      // If we haven't '/n' in the end of str, we add it
    {
         *(str + len - 2) = '\n';
         *(str + len - 1) = '\0';
    }

    if (fclose (f) != 0)
    {
        onegin_exit_code = FromFileToStr_CODE + ONEGIN_FILE_CLOSE_ERROR;
        return -1;
    }

    return 0;
} 

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FromStrToFile (string* str, char* file_name, unsigned countStr, char* mode)
{
    assert (str != NULL);
    assert (file_name != NULL);
    assert (mode != NULL);

    FILE* f = fopen (file_name, mode);

    if (f == NULL)
    {
        onegin_exit_code = FromStrToFile_CODE + ONEGIN_FILE_OPEN_ERROR;
        return -1;
    }

    int checker = fseek (f, 0, SEEK_END);

    if (checker != 0)
    {
        onegin_exit_code = FromStrToFile_CODE + ONEGIN_FSEEK_ERROR;
        return -1;
    }

    for (unsigned i = 0; i < countStr; ++i)
        if ((*(str + i)).len > 2)                       //We skip "empty" string (which have less then 2 symbols)
            for (unsigned j = 0; j < str[i].len; ++j)
                fputc ((int) str[i].start[j], f);
    
    fputc ('\n', f); 

    if (fclose (f) != 0)
    {
        onegin_exit_code = FromStrToFile_CODE + ONEGIN_FILE_CLOSE_ERROR;
        return -1;
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

string init (unsigned length, char* start)
{
    assert (start != NULL);

    string str;

    str.len   = length;
    str.start = start;

    return str;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FillPMassive (string* pointers_to_str, char* file_copy, unsigned countStr, unsigned countSym)
{
    assert (pointers_to_str != NULL);
    assert (file_copy != NULL);
    
    int cur_len = 0;
    char* cur_p = file_copy;
    int j = 0;

    for (int i = 0; i < countStr; ++i)
    {
        cur_p = file_copy + j;
        cur_len = 0;

        while(file_copy[j] != '\n' and j < countSym)
        {
            j++;
            cur_len++;
        }

        if (file_copy[j] == '\n')
            file_copy[j] = '\0';

        j++;
        cur_len++;

        pointers_to_str[i].len      = cur_len;
        pointers_to_str[i].start    = cur_p;     
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int PrintStr (char* str, string* str1, unsigned countStr)
{
    assert (str != NULL);
    assert (str1 != NULL);

    for (unsigned i = 0; i < countStr; ++i)
        printf ("%s\n", str1[i].start);

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrCompare (const void* s1, const void* s2)
{
    assert (s1 != NULL);
    assert (s2 != NULL);
 
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

        if (cur_sym1 != cur_sym2)
            return (int) cur_sym1 - (int) cur_sym2;

        i++;
        j++;
    }

    return (int) (*str1).len - (int) (*str2).len;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrRevCompare (const void* s1, const void* s2)  
{
    assert (s1 != NULL);
    assert (s2 != NULL);    

    string* str1 = (string*) s1;
    string* str2 = (string*) s2; 

    if ((*str1).len == 1)
        return 1;
    if ((*str2).len == 1)
        return -1; 

    int i = (*str1).len - 1, j = (*str2).len - 1;

    char cur_sym1 = *((*str1).start + i);
    char cur_sym2 = *((*str2).start + j);

    while (!isalpha (cur_sym1))
    {
        i--;
        cur_sym1 = *((*str1).start + i);
    }

    while (!isalpha (cur_sym2))
    {
        j--;
        cur_sym2 = *((*str2).start + j);
    }

    while (i >= 0 and j >= 0)
    {
        cur_sym1 = *((*str1).start + i);
        cur_sym2 = *((*str2).start + j);

        if (isalpha (cur_sym1) and isalpha (cur_sym2) and cur_sym1 != cur_sym2)
            return LettersCmp (cur_sym1, cur_sym2);

        else if (isalpha (cur_sym1) and !isalpha (cur_sym2))
            i++;

        else if (!isalpha (cur_sym1) and isalpha (cur_sym2))
            j++;
        
        i--;
        j--;
    }

    return (int) (*str1).len - (int) (*str2).len;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void QuickSort (void* p, size_t number, size_t size_el, int (*comparator) (const void*, const void*))
{
    assert (p != NULL);
    assert (comparator != NULL);

    char* start = (char*) p;

    int right = number - 1;

    int last = 0;

    int tmp = right / 2;

    if (0 >= right)
        return;

    JSwap (start, start + tmp * size_el, size_el);

    for (int i = 1; i <= right; ++i)
        if (comparator (start + i * size_el, start) < 0)
        {
            ++last;
            JSwap (start + i * size_el, start + last * size_el, size_el);
        }

    JSwap (start + last * size_el, start, size_el);

    QuickSort (start, last, size_el, comparator);
    QuickSort (start + (last + 1) * size_el, number - last - 1, size_el, comparator);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int JSwap (void* el1, void* el2, size_t size_el)
{
    assert (el1 != NULL);
    assert (el2 != NULL);

    char* s1 = (char*) el1;
    char* s2 = (char*) el2;
    char tmp;

    for (unsigned i = 0; i < size_el; i++)
    {
        tmp = s1[i];
        s1[i] = s2[i];
        s2[i] = tmp;
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int OrigStrToFile (char* str, char* file_name, char* mode)
{
    assert (str != NULL);
    assert (file_name != NULL);
    assert (mode != NULL);

    FILE* f = fopen (file_name, mode);

    if (f == NULL)
    {
        onegin_exit_code = OrigStrToFile_CODE + ONEGIN_FILE_OPEN_ERROR;
        return -1;
    }

    fprintf (f, "%s", str);

    fputc ('\n', f);

    if (fclose (f) != 0)
    {
        onegin_exit_code = OrigStrToFile_CODE + ONEGIN_FILE_CLOSE_ERROR;
        return -1;
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LettersCmp (char a, char b)
{
    a = tolower (a);
    b = tolower (b);

    if (a != b)
        return (a > b) ? 1 : -1;
    
    else    
        return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Onegin_PrintExitCode ()
{
    int tmp = onegin_exit_code % 256;

    if (tmp == NO_EXCEPTIONS_ONEGIN)
    {
        printf ("No exceptions\n");
        return;
    }

    switch (tmp)
    {
        case ONEGIN_FILE_OPEN_ERROR:
            printf ("Failed to open file in ");
            break;

        case ONEGIN_FILE_CLOSE_ERROR:
            printf ("Failed to close file in ");
            break;

        case ONEGIN_FREAD_ERROR:
            printf ("fread() returns incorrect value in ");
            break;

        case ONEGIN_FSEEK_ERROR:
            printf ("fseek() returns incorrect value in ");
            break;

        default:
            printf ("Unknown exception code in ");
            break;
    }

    tmp = onegin_exit_code / 256 * 256;

    switch (tmp)
    {
        case CountSymbols_CODE:
            printf ("CountSymblos() ");
            break;

        case CountStr_CODE:
            printf ("CountStr() ");
            break;

        case FromFileToStr_CODE:
            printf ("FromFileToStr() ");
            break;

        case FromStrToFile_CODE:
            printf ("FromStrToFile() ");
            break;

        case init_CODE:
            printf ("init() ");
            break;

        case FillPMassive_CODE:
            printf ("FillPMassive() ");
            break;

        case PrintStr_CODE:
            printf ("PrintStr() ");
            break;

        case StrCompare_CODE:
            printf ("StrCompare() ");
            break;

        case StrRevCompare_CODE:
            printf ("StrRevCompare() ");
            break;

        case QuickSort_CODE:
            printf ("QuickSort() ");
            break;

        case JSwap_CODE:
            printf ("JSwap() ");
            break;

        case OrigStrToFile_CODE:
            printf ("OrigStrToFile() ");
            break;
        
        default:
            printf ("unknown ");
            break;
    }

    printf ("func\n");
}