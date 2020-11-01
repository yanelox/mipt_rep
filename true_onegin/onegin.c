#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <locale.h> 

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
                                                                                      
#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Enumerate of code of errors
*/

enum exit_codes 
{
    NO_EXCEPTIONS       = 0x000000, //If all is OK
    FILE_OPEN_ERROR     = 0x000002,
    FREAD_ERROR         = 0x000004,
    FSEEK_ERROR         = 0x000007,
    FILE_CLOSE_ERROR    = 0x000009
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Enumerate of code of functions to detect where was detected errors
*/

enum func_codes
{
    CountSymbols_CODE   = 0x222200,
    CountStr_CODE       = 0x222400,
    FromFileToStr_CODE  = 0x222700,
    FromStrToFile_CODE  = 0x222900,
    init_CODE           = 0x224200,
    FillPMassive_CODE   = 0x224400,
    PrintStr_CODE       = 0x224700,
    StrCompare_CODE     = 0x224900,
    StrRevCompare_CODE  = 0x227200,
    QuickSort_CODE      = 0x227400,
    JSwap_CODE          = 0x227700,
    OrigStrToFile_CODE  = 0x227900
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Global variable which contents exit code 
*/

int onegin_exit_code = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  New type string: start - pointer to start of string, len - length of string
*/

typedef struct 
{
    unsigned len; //size_t

    char* start;
}
string;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which count number of symbols (string)

    @param  [in] file_name Pointer to string where is necessary text
    
    @return Returns count of symbols in string or -1 if smth incorrect
*/

long int CountSymbols   (char* file_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which count numbers of strings in text (string_name)

    @param  [in] string_name    Pointer to string with text where
                                we want to count strings

    @return Returns count os string in text
*/

long int CountStr       (char* string_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which copy text from file with name file_name to str

    @param  [in] file_name Name of file which we want to read
    @param  [in] str Pointer to string where will be written out text
    @param  [in] len Maximum number of symbols which we will read

    @return Returns ALL_OK if there isn't any exeptions and 
            SMTH_WRONG in all another cases
*/

int FromFileToStr       (char* file_name, char* str, unsigned len);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which copy text from string to file using type_string massive

    @param  [in] str Pointer to massive with pointers to starts of string (which
                ends on '\n') in our string. We use this massive to sort our text
                using function qsort
    @param  [in] file_name Name of file where we copy our string
    @param  [in] count Number of symbols which we want to copy
    @param  [in] mode Parameter which is used in "fopen" fuction

    @return Returns ALL_OK if there isn't any exeptions and 
            SMTH_WRONG in all another cases
*/

int FromStrToFile       (string* str, char* file_name, unsigned count, char* mode);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Initialization function for type "string"
*/

string init             (unsigned length, char* start);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which fill string massive using "file_copy" text 

    @param  [in] pointers_to_str Pointer to massive with type "string" which
                we fill 
    @param  [in] file_copy Text which from we fill "pointers_to_str"
    @param  [in] countStr Number of strings in our "file_copy"
    @param  [in] countSym Number of symbols in our "file_copy"

    @return Returns ALL_OK if there isn't any exeptions and 
            SMTH_WRONG in all another cases
*/

int FillPMassive        (string* pointers_to_str, char* file_copy, 
                        unsigned countStr, unsigned countSym);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which print text taking into account string massive which we sort

    @param  [in] str String with text which we want to print
    @param  [in] str1 Pointer to "string" massive which defines the output order
    @param  [in] countStr Number of strings in text

    @return Returns ALL_OK if there isn't any exeptions and 
            SMTH_WRONG in all another cases
*/

int PrintStr            (char* str, string* str1, unsigned countStr);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which compare two "string" elements in alhabet order from start 
            to end

    @param  [in] s1 Pointer to first element 
    @param  [in] s2 Pointer to second element

    @return Number above zero if s1 should be after s2, below zero if s1 should be
            before s2, zero if s1 and s2 is same

    @note   There are strange types of input parameters because this function can be used 
            whith qsort() function
*/

int StrCompare          (const void* s1, const void* s2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which compare two "string" elements in alphabet order from end to 
            start 

    @param [in] s1 Pointer to first element 
    @param [in] s2 Pointer to second element

    @return Number above zero if s1 should be after s2, below zero if s1 should be
            before s2, zero if s1 and s2 is same

    @note   There are strange types of input parameters because this function can be used 
            whith qsort() function
*/

int StrRevCompare       (const void* s1, const void* s2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Quick sort realization for any massive

    @param  [in] p              Pointer to "string" massive
    @param  [in] number         Size of sorted massive
    @param  [in] size_el        Size of one element of massive in bytes
    @param  [in] comparator     Function which compare two elements
*/

void QuickSort          (void* p, size_t number, size_t size_el, 
                        int (*comparator) (const void*, const void*));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which swap two elements of the same data types using their 
            size in bytes

    @param  [in] el1        Pointer to first element
    @param  [in] el2        Pointer to second element
    @param  [in] size_el    Size of elements in bytes

    @return Returns 0 if all correct
*/

int JSwap               (void* el1, void* el2, size_t size_el);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which print text to file

    @param  [in] str Pointer tp start of text
    @param  [in] file_name Name of file wher we want to print
    @param  [in] mode Parameter which is used in fopen() function

    @return Returns ALL_OK if there isn't any exeptions and 
            SMTH_WRONG in all another cases
*/

int OrigStrToFile       (char* str, char* file_name, char* mode);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which check which letter is less in alphaber order

    @param  [in] a First letter
    @param  [in] b Second letter 

    @return Value above zero if a is higher, below zero if b is higher, zero if a and
            b is same letters

    @note   This function was written verify cases with capital letters and lowercase
            letters (because 'a' and 'A' has different codes in table of codings)
*/

int LettersCmp          (char a, char b);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char* argv[])
{   
    assert (argc >= 2);

    long int countStr = 0;
    long int countSym = 0;

    char* file_for_sort = argv[1];
    char* sorted_file   = argv[2];

    countSym = CountSymbols (file_for_sort);

    char* file_copy = (char*) calloc (countSym + 2, sizeof(char));                 

    FromFileToStr (file_for_sort, file_copy, countSym);

    countStr = CountStr (file_copy);

    string* pointers_to_str = (string*) calloc (countStr, sizeof (string));

    FillPMassive (pointers_to_str, file_copy, countStr, countSym);
    
    QuickSort (pointers_to_str, countStr, sizeof(string), StrCompare);

    FromStrToFile (pointers_to_str, sorted_file, countStr, "w");
    
    QuickSort (pointers_to_str, countStr, sizeof(string), StrRevCompare);

    FromStrToFile (pointers_to_str, sorted_file, countStr, "a");
    
    OrigStrToFile (file_copy, sorted_file, "a");
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

long int CountSymbols (char* file_name)
{
    assert (file_name != NULL);

    long int count_sym;

    FILE* f = fopen (file_name, "r");

    if (f == NULL)
    {
        onegin_exit_code = CountSymbols_CODE + FILE_OPEN_ERROR;
        return -1;
    }

    fseek (f, 0, SEEK_END);

    count_sym = ftell (f);

    fseek (f, 0, SEEK_SET);

    count_sym -= ftell (f);

    if (fclose (f) != 0)
    {
        onegin_exit_code = CountSymbols_CODE + FILE_CLOSE_ERROR;
        return -1;
    }

    return count_sym;
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

    unsigned checker = fread (str, sizeof(char), len, f);

    if (checker != len)
    {
        onegin_exit_code = FromFileToStr_CODE + FREAD_ERROR;
        return -1;
    }

    if ( *(str + len - 1) != '\n')      // If we haven't '/n' in the end of str, we add it
    {
         *(str + len) = '\n';
         *(str + len + 1) = '\0';
    }

    if (fclose (f) != 0)
    {
        onegin_exit_code = FromFileToStr_CODE + FILE_CLOSE_ERROR;
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
        onegin_exit_code = FromStrToFile_CODE + FILE_OPEN_ERROR;
        return -1;
    }

    int checker = fseek (f, 0, SEEK_END);

    if (checker != 0)
    {
        onegin_exit_code = FromStrToFile_CODE + FSEEK_ERROR;
        return -1;
    }

    for (unsigned i = 0; i < countStr; ++i)
        if ((*(str + i)).len > 2)                       //We skip "empty" string (which have less then 2 symbols)
            for (unsigned j = 0; j < str[i].len; ++j)
                fputc ((int) str[i].start[j], f);
    
    fputc ('\n', f); 

    if (fclose (f) != 0)
    {
        onegin_exit_code = FromStrToFile_CODE + FILE_CLOSE_ERROR;
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
        for (unsigned j = 0; j < str1[i].len; ++j)
            printf ("%c", str1[i].start[j]); 

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

        if (isalpha (cur_sym1) and isalpha (cur_sym2) and cur_sym1 != cur_sym2)
            return LettersCmp (cur_sym1, cur_sym2);
        
        else if (isalpha (cur_sym1) and !isalpha (cur_sym2))
            i--;

        else if (!isalpha (cur_sym1) and isalpha (cur_sym2))
            j--;
        
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
        onegin_exit_code = OrigStrToFile_CODE + FILE_OPEN_ERROR;
        return -1;
    }

    fprintf (f, "%s", str);

    fputc ('\n', f);

    if (fclose (f) != 0)
    {
        onegin_exit_code = OrigStrToFile_CODE + FILE_CLOSE_ERROR;
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

void PrintExit ()
{
    int tmp = onegin_exit_code % 256;

    if (tmp == NO_EXCEPTIONS)
    {
        printf ("No exceptions\n");
        return;
    }

    switch (tmp)
    {
        case FILE_OPEN_ERROR:
            printf ("Failed to open file in ");
            break;

        case FILE_CLOSE_ERROR:
            printf ("Failed to close file in ");
            break;

        case FREAD_ERROR:
            printf ("fread() returns incorrect value in ");
            break;

        case FSEEK_ERROR:
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