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
    {{2, "in"},     22},
    {{4, "push"},   24},
    {{3, "mul"},    27},
    {{3, "add"},    29},
    {{3, "sub"},    42},
    {{3, "div"},    44},
    {{3, "out"},    47},
    {{3, "jmp"},    49},
    {{3, "hlt"},    99}
};

const size_t number_commands = 9;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum assm_input_types
{
    ASSM_COMMAND_CODE    = 2200,
    ASSM_DOUBLE_CODE     = 2400,
    ASSM_INT_CODE        = 2700,
    ASSM_LABEL_CODE      = 2900,
    ASSM_ERROR_CODE      = 9900
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum assm_exit_codes
{
    NO_EXCEPTIONS_ASSM      = 00,
    ASSM_INCORRECT_COMMAND  = 22,
    ASSM_INPUT_EXCEPTION    = 24,
    ASSM_FOPEN_ERROR        = 27,
    ASSM_FCLOSE_ERROR       = 29
};

int assm_exit_code = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum assm_func_codes
{
    ASSM_WHICHCOMMAND_CODE   = 2200,
    ASSM_TYPEOFINPUT_CODE    = 2400,
    ASSM_ASSEMBLING_CODE     = 2700
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const char delim[] = " \n";

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define CheckExitCode() assert(assm_exit_code == NO_EXCEPTIONS_ASSM);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned typeOfInput        (char* lexem, size_t len);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assembling             (char* code_file, char* code_copy);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assm_PrintExitCode     ();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char* argv[])
{
    if (argc != 3)
    {
        printf ("Incorrect arguments\n");
        return 0;
    }

    char* assm_file = argv[1];
    char* code_file = argv[2];

    char* code_copy = NULL;

    long int count_sym = 0;

    count_sym = CountSymbols (assm_file);

    if (count_sym == -1)
    {
        Onegin_PrintExitCode();
        return 0;
    }

    code_copy = (char*) calloc (count_sym, sizeof (char));

    if (code_copy == NULL)
    {
        printf ("Allocation error\n");
        return 0;
    }

    //printf ("lol\n");

    if (FromFileToStr (assm_file, code_copy, count_sym) == -1)
    {
        Onegin_PrintExitCode();
        return 0;
    }

    Assembling (code_file, code_copy);

    printf ("Assembling succesfull\n");

    free (code_copy);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned typeOfInput (char* lexem, size_t len)
{
    assert (lexem != NULL);

    unsigned res = 0;

    string tmp = {len, lexem};

    for (unsigned i = 0; i < len; ++i)
        if (isalpha (lexem[i]))
        {
            if (res == 0)
                res = ASSM_COMMAND_CODE;

            else if (res != ASSM_COMMAND_CODE)
            {
                assm_exit_code = ASSM_INPUT_EXCEPTION + ASSM_TYPEOFINPUT_CODE;
                return ASSM_ERROR_CODE;
            }
        }

        else if (isdigit (lexem[i]))
        {
            if (res == 0)
                res = ASSM_INT_CODE;

            else if ((res != ASSM_INT_CODE) and (res != ASSM_DOUBLE_CODE))
            {
                assm_exit_code = ASSM_INPUT_EXCEPTION + ASSM_TYPEOFINPUT_CODE;
                return ASSM_ERROR_CODE;
            }
        }

        else if (lexem[i] == '.')
        {
            if (res == ASSM_INT_CODE)
                res = ASSM_DOUBLE_CODE;

            else
            {
                assm_exit_code = ASSM_INPUT_EXCEPTION + ASSM_TYPEOFINPUT_CODE;
                return ASSM_ERROR_CODE;
            }
        }

        else
        {
            assm_exit_code = ASSM_INPUT_EXCEPTION + ASSM_TYPEOFINPUT_CODE;
            return ASSM_ERROR_CODE;
        }

    if (res == ASSM_COMMAND_CODE)
        for (unsigned i = 0; i < number_commands; ++i)
            if (StrCompare (&tmp, &commands[i].text) == 0)
            {
                res += commands[i].code;
                break;
            }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assembling (char* code_file, char* code_copy)
{
    assert (code_file);
    assert (code_copy);

    FILE* f = fopen (code_file, "w");

    if (f == NULL)
    {
        assm_exit_code = ASSM_FOPEN_ERROR + ASSM_ASSEMBLING_CODE;
        return;
    }

    char* lexem = NULL;

    int prog_status = 1;
    int input = -1;
    int half_input = -1;

    lexem = strtok (code_copy, delim);

    while (lexem and prog_status)
    {
        input = typeOfInput (lexem, strlen (lexem));

        half_input = input / 100 * 100;

        CheckExitCode();

        switch (half_input)
        {
            case ASSM_COMMAND_CODE:
                CheckExitCode();

                fprintf (f, "%d\n", input % 100);
                break;

            case ASSM_DOUBLE_CODE:
                fprintf (f, "%s\n", lexem);
                break;

            case ASSM_INT_CODE:
                fprintf (f, "%s\n", lexem);
                break;

            default:
                assm_exit_code = ASSM_ASSEMBLING_CODE + ASSM_INPUT_EXCEPTION;
                prog_status = 0;
                break;

        }

        lexem = strtok (NULL, delim);
    }

    if (fclose (f) != 0)
    {
        assm_exit_code = ASSM_ASSEMBLING_CODE + ASSM_FCLOSE_ERROR;
        return;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assm_PrintExitCode ()
{
    int error_code  = assm_exit_code % 100;
    int func_code   = assm_exit_code / 100 * 100;

    int no_error_status = 0;

    switch (error_code)
    {
        case NO_EXCEPTIONS_ASSM:
            printf ("No exception found\n");
            no_error_status = 1;
            break;

        case ASSM_INCORRECT_COMMAND:
            printf ("Incorrect assembler command found in ");
            break;

        case ASSM_INPUT_EXCEPTION:
            printf ("Incorrect input data found in ");
            break;

        case ASSM_FOPEN_ERROR:
            printf ("File opening error in ");
            break;

        case ASSM_FCLOSE_ERROR:
            printf ("File closing error in ");
            break;

        default:
            printf ("Unkwonw error in ");
            break;
    }

    if (no_error_status)
        return;

    switch (func_code)
    {
        case ASSM_WHICHCOMMAND_CODE:
            printf ("WhichCommand() ");
            break;

        case ASSM_TYPEOFINPUT_CODE:
            printf ("typeOfInput() ");
            break;

        case ASSM_ASSEMBLING_CODE:
            printf ("Assembling() ");
            break;

        default:
            printf ("unknown ");
            break;
    }

    printf ("func\n");
}