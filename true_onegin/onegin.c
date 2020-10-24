#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <locale.h> 

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Enumerate of returned values by fucntion which used to catch errors

enum returned_values 
{
    ALL_OK = 42,            // All is OK
    SMTH_WRONG = - 42       // Something not OK
};

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
    \brief  Function, which count number of symbols and strings in text (string)

    @param  [in] file_name Pointer to string where is necessary text
    @param  [in] countStr Pointer to variable where will be written number of strings
    @param  [in] countSym Pointer to variable where will be written number of symbols
    
    @return Returns ALL_OK if there isn't any exeptions and 
            SMTH_WRONG in all another cases
*/

int FileSizeInfo           (char* file_name, unsigned* countStr, unsigned* countSym);

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

/*! //TODO delete
    \brief  Function which checking a is letter or other symbols

    @param  [in] a Symbol which we want to check

    @return 1 if a is letter and 0 if a isn't letter
*/

int IsLetter            (char a);

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
    \brief  Quick sort realization for string's

    @param  [in] mass Pointer to "string" massive
    @param  [in] size Size of sorted massive
    @param  [in] CompareFunc Function which compare two strings

    @note   It doesn't work, don't use it
    //TODO run with Valgrind and FLAGS
*/

void StrQuickSort       (string* mass, unsigned size, 
                        int ( * CompareFunc ) ( const void *, const void * ));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which swap two "string" elements

    @param  [in] s1 Pointer to first element
    @param  [in] s2 Pointer to second element
*/

int StrSwap             (string* s1, string* s2);

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
// letters_cmp
int TrueDiffBtwLetters  (char a, char b);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which is used in StrQuickSort

    @param  [in] mass Pointer to sorted massive
    @param  [in] low First index from we sort
    @param  [in] high Last element until we sort
    @param  [in] CompareFunc Function which compare two strings

    @return Number of supporting element

    @note It doesn't work, don't use it
*/

int QPartition          (string* mass, int low, int high, 
                        int (* CompareFunc)(const void* el1, const void* el2));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


int main (int argv, char* argc[])
{   
    assert (argv >= 2);

    unsigned countStr = 0;
    unsigned countSym = 0;

    char* file_for_sort = argc[1];            
    char* sorted_file   = argc[2];

    Check( GetValues (file_for_sort, &countStr, &countSym) );
    Check(exit_code);

    //assert (checker == ALL_OK);

    char* file_copy = (char*) calloc (countSym + 2, sizeof(char)); 

    assert (file_copy != NULL);                

    checker = FromFileToStr (file_for_sort, file_copy, countSym);
    assert (checker == ALL_OK);

    string pointers_to_str[countStr]; //Do not work

    checker = FillPMassive (pointers_to_str, file_copy, countStr, countSym);
    assert (checker == ALL_OK);

    qsort (pointers_to_str, countStr, sizeof(string), StrCompare);

    checker = FromStrToFile (pointers_to_str, sorted_file, countStr, "w");
    assert (checker == ALL_OK);

    qsort (pointers_to_str, countStr, sizeof(string), StrRevCompare);

    checker = FromStrToFile (pointers_to_str, sorted_file, countStr, "a");
    assert (checker == ALL_OK);

    checker = OrigStrToFile (file_copy, sorted_file, "a");
    assert (checker == ALL_OK);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetValues (char* file_name, unsigned* countStr, unsigned* countSym)
{
    assert(file_name);
    a
    a

    FILE* f = fopen (file_name, "r");
    //access F_OK
    if (f == NULL and countStr != 0 and countSym != 0)
        return SMTH_WRONG;
    //TODO OpenFile

    int cur_sym = 0, last_sym = 0;

    *countSym = 0;
    *countStr = 0;

    //TODO fread
    //TODO How to get file size c (fseek)
    while((cur_sym = fgetc (f)) != EOF)
    {
        (*countSym)++;

        if (cur_sym == '\n')
            (*countStr)++;

        last_sym = cur_sym;
    }

    if (last_sym != '\n')
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

    // comment
    if ( *(str + len - 1) != '\n')
    {
         *(str + len) = '\n';
         *(str + len + 1) = '\0';
    }

    fclose (f);

    return ALL_OK;
} 

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FromStrToFile (string* str, char* file_name, unsigned countStr, char* mode)
{
    FILE* f = fopen (file_name, mode);

    if (f == NULL)
        return SMTH_WRONG;

    int checker = fseek (f, 0, SEEK_END);

    if (checker != 0)
        return SMTH_WRONG;

    for (unsigned i = 0; i < countStr; ++i)
        if ((*(str + i)).len > 2) //Commemt
            for (unsigned j = 0; j < (str[i].len; j++)
                fputc ((int) str[i].start[j], f);
    
    fprintf (f, "\n"); //fputc

    fclose (f); // TODO function

    return ALL_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

string init (unsigned length, char* start)
{
    string str;

    str.len   = length;
    str.start = start;

    return str;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int FillPMassive (string* pointers_to_str, char* file_copy, unsigned countStr, unsigned countSym)
{
    asert()!!!!!!!!!
    if (file_copy == NULL or pointers_to_str == NULL)
        return SMTH_WRONG;
    //TODO ADD ALL WARINGS AND FIX THEM
    int cur_len = 0;
    char* cur_p = file_copy;

    for (i = 0; i < countStr; i++)
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

        pointers_to_str[i] = //new_string (cur_len, cur_p);        
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
            printf ("%c", *((*(str1 + i)).start + j)); //[][]           *(str + i) ======= i]

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
            return TrueDiffBtwLetters (cur_sym1, cur_sym2);
        
        else if (isalpha() (cur_sym1) and !IsLetter (cur_sym2))
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
    return (('a' <= a) and (a <= 'z')) or (('A' <= a) and (a <= 'Z'));;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrRevCompare (const void* s1, const void* s2)  
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
            return TrueDiffBtwLetters (cur_sym1, cur_sym2);

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

void StrQuickSort (string* mass, unsigned size, int (* CompareFunc)(const void* el1, const void* el2)) //QuickSort не работает не юзать !!!!!!!!!!!
{
    int left = 0;
    int right = size - 1;

    if (right < 0)
        return;
    
    if (left < right)
    {
        int p = Partition (mass, left, right, CompareFunc);

        StrQuickSort (mass, p + 1, CompareFunc);

        StrQuickSort (mass + p + 1, size - p - 1, CompareFunc);
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StrSwap (string* s1, string* s2)
{
    string swap_tmp = *s1;
    *s1 = *s2;
    *s2 = swap_tmp;

    return ALL_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int OrigStrToFile (char* str, char* file_name, char* mode)
{
    FILE* f = fopen (file_name, mode);

    if (f == NULL)
        return SMTH_WRONG;

    fprintf (f, "%s", str);

    fprintf (f, "\n");

    fclose (f);

    return ALL_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int TrueDiffBtwLetters (char a, char b)
{
    //tolower!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if ((a >= 'A') and (a <= 'Z'))
        a += 'a' - 'A';

    if ((b >= 'A') and (b <= 'Z'))
        b += 'a' - 'A';

    return a - b;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int Partition (string* mass, int low, int high, int (* CompareFunc)(const void* el1, const void* el2)) //не работает, не юзать!!!!!!!
{
    string sup_el = mass[(low + high) / 2];

    int left = low - 1;
    int right = high + 1;

    for (;;)
    {
        do
            left++;
        while (CompareFunc ((const void*) mass + left, (const void*) &sup_el) < 0);

        do
            right--;
        while (CompareFunc ((const void*) mass + right, (const void*) &sup_el) > 0);
        
        if (left >= right)
            return right;

        StrSwap (mass + left, mass + right);

        left++;
        right--;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
