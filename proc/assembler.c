#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "special_onegin.c"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct
{
    string text;

    int code;

} Command;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Command commands[] =
{
    {{2, "in"},     0x22},
    {{4, "push"},   0x24},
    {{3, "mul"},    0x27},
    {{3, "sum"},    0x29},
    {{3, "add"},    0x42},
    {{3, "sub"},    0x44},
    {{3, "div"},    0x47},
    {{3, "out"},    0x49},
    {{3, "hlt"},    0x72}
};

const size_t number_commands = 8;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum assm_input_types
{
    COMMAND_CODE    = 0x2200,
    DOUBLE_CODE     = 0x2400,
    INT_CODE        = 0x2700,
    ERROR_CODE      = 0x9900
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum assm_exit_codes
{
    NO_EXCEPTIONS_ASSM  = 0x0000,
    INCORRECT_COMMAND   = 0x2222,
    INPUT_EXCEPTION     = 0x2224
};

unsigned assm_exit_code = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const char delim[] = " \n";

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define CheckExitCode() assert(assm_exit_code == NO_EXCEPTIONS_ASSM);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int WhichCommand (char* lexem, size_t len);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned typeOfInput (char* lexem, size_t len);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int IsNumber (char a);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assembling (char* code_file, char* code_copy);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char* argv[])
{
    assert ((argv[2][0] == '-') and (argv[2][1] == 'o'));

    char* assm_file = argv[1];
    char* code_file = argv[3];

    char* code_copy = NULL;

    long int countSym = 0;

    countSym = CountSymbols (assm_file);
    code_copy = (char*) calloc (countSym + 2, sizeof (char));

    FromFileToStr (assm_file, code_copy, countSym);

    Assembling (code_file, code_copy);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int WhichCommand (char* lexem, size_t len)
{
    assert (lexem != NULL);

    string tmp = {len, lexem};

    for (unsigned i = 0; i < number_commands; ++i)
        if (StrCompare (&tmp, &commands[i].text) == 0)
            return commands[i].code;

    assm_exit_code = INCORRECT_COMMAND;

    return -1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned typeOfInput (char* lexem, size_t len)
{
    assert (lexem != NULL);

    unsigned res = 0;

    for (unsigned i = 0; i < len; ++i)
        if (isalpha (lexem[i]))
        {
            if (res == 0)
                res = COMMAND_CODE;

            else if (res != COMMAND_CODE)
            {
                assm_exit_code = INPUT_EXCEPTION;
                return ERROR_CODE;
            }
        }

        else if (IsNumber (lexem[i]))
        {
            if (res == 0)
                res = INT_CODE;

            else if ((res != INT_CODE) and (res != DOUBLE_CODE))
            {
                assm_exit_code = INPUT_EXCEPTION;
                return ERROR_CODE;
            }
        }

        else if (lexem[i] == '.')
        {
            if (res == INT_CODE)
                res = DOUBLE_CODE;

            else
            {
                assm_exit_code = INPUT_EXCEPTION;
                return ERROR_CODE;
            }
        }

        else
        {
            assm_exit_code = INPUT_EXCEPTION;
            return ERROR_CODE;
        }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int IsNumber (char a)
{
    if ((a - '0' >= 0) and (a - '0' < 10))
        return 1;

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assembling (char* code_file, char* code_copy)
{
    FILE* f = fopen (code_file, "w");

    char* lexem = NULL;
    int tmp = -1;

    lexem = strtok (code_copy, delim);

    while (lexem)
    {
        tmp = typeOfInput (lexem, strlen (lexem));

        CheckExitCode();

        switch (tmp)
        {
            case COMMAND_CODE:
                tmp = WhichCommand (lexem, strlen (lexem));
                
                CheckExitCode();

                fprintf (f, "%X\n", tmp);

                break;

            case DOUBLE_CODE:
                fprintf (f, "%s\n", lexem);
                break;

            case INT_CODE:
                fprintf (f, "%s\n", lexem);
                break;

            default:
                assert (0);
                break;

        }

        lexem = strtok (NULL, delim);
    }

    fclose (f);
}