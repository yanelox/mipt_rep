//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Enumerate of code of errors
*/

enum onegin_exit_codes 
{
    NO_EXCEPTIONS_ONEGIN    = 0x000000, //If all is OK
    ONEGIN_FILE_OPEN_ERROR  = 0x000002,
    ONEGIN_FREAD_ERROR      = 0x000004,
    ONEGIN_FSEEK_ERROR      = 0x000007,
    ONEGIN_FILE_CLOSE_ERROR = 0x000009
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Enumerate of code of functions to detect where was detected errors
*/

enum onegin_func_codes
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

extern int onegin_exit_code;

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

string StrCtor          (unsigned length, char* content);

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

int PrintStr            (string* str1, unsigned countStr);

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

/*!
    \brief  Function which print info about exception using exception code 
            which stored in onegin_exit_code variabe
*/

void Onegin_PrintExitCode   ();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StrDtor                (string str);