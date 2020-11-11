#include <stdio.h>
#include <stdlib.h>
#include "special_onegin.c"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum disassm_exit_codes
{
    DISASSM_NO_EXCEPTIONS       = 00,
    DISASSM_FOPEN_ERROR         = 22,
    DISASSM_FCLOSE_ERROR        = 24,
    DISASSM_INCORRECT_COMMAND   = 27   
};

enum disassm_func_codes
{
    DISASSM_DISSASSEMBLING_CODE = 2200
};

int disassm_exit_code = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

string commands [] =
{
    {2, "in"},
    {4, "push"},
    {3, "mul"},
    {3, "add"},
    {3, "sub"},
    {3, "div"},
    {3, "out"},
    {3, "hlt"}
};

enum dissass_comands_numbers
{
    DISS_IN_CODE        = 22,
    DISS_PUSH_CODE      = 24,
    DISS_MUL_CODE       = 27,
    DISS_ADD_CODE       = 29,
    DISS_SUB_CODE       = 42,
    DISS_DIV_CODE       = 44,
    DISS_OUT_CODE       = 47,
    DISS_HLT_CODE       = 99
};

const size_t number_commands = 8;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void DissAssembling (char* code_copy, char* assm_file);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char* argv[])
{
    if (argc != 3)
    {
        printf ("Incorrect arguments\n");
        return 0;        
    }
    
    char* code_file = argv[1];
    char* assm_file = argv[2];

    char* code_copy = NULL;

    long count_sym = CountSymbols (code_file);

    if (count_sym == -1)
    {
        Onegin_PrintExitCode ();
        return 0;
    }

    code_copy = (char*) calloc (count_sym, sizeof (char));

    if (code_copy == NULL)
    {
        printf ("Memory allocation error\n");
        return 0;
    }

    if (FromFileToStr (code_file, code_copy, count_sym) == -1)
    {
        Onegin_PrintExitCode ();
        return 0;
    }

    DissAssembling (code_copy, assm_file);

    printf ("Dissassembling done\n");
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void DissAssembling (char* code_copy, char* assm_file)
{
    assert (code_copy != NULL);
    assert (assm_file != NULL);

    int cur_input = 0;
    int prog_status = 1;
    int shift = 0;
    double input_value = 0;

    FILE* file = fopen (assm_file, "w");

    if (file == NULL)
    {
        disassm_exit_code = DISASSM_DISSASSEMBLING_CODE + DISASSM_FOPEN_ERROR;
        return;
    }

    while (prog_status)
    {
        sscanf (code_copy, "%d%n", &cur_input, &shift);

        code_copy += shift;

        switch (cur_input)
        {
            case DISS_IN_CODE:
                fprintf (file, "%s", commands[0].start);

                break;

            case DISS_PUSH_CODE:
                fprintf (file, "%s ", commands[1].start);

                sscanf (code_copy, "%lg%n", &input_value, &shift);

                code_copy += shift;

                fprintf (file, "%lg", input_value);

                break;

            case DISS_MUL_CODE:
                fprintf (file, "%s", commands[2].start);

                break;

            case DISS_ADD_CODE:
                fprintf (file, "%s", commands[3].start);

                break;

            case DISS_SUB_CODE:
                fprintf (file, "%s", commands[4].start);

                break;

            case DISS_DIV_CODE:
                fprintf (file, "%s", commands[5].start);

                break;

            case DISS_OUT_CODE:
                fprintf (file, "%s", commands[6].start);

                break;

            case DISS_HLT_CODE:
                fprintf (file, "%s", commands[7].start);

                prog_status = 0;

                break;

            default:
                prog_status = 0;
                disassm_exit_code = DISASSM_INCORRECT_COMMAND + DISASSM_DISSASSEMBLING_CODE;

                break;
        }

        fprintf (file, "\n");
        
    }

    if (fclose (file) != 0)
    {
        disassm_exit_code = DISASSM_DISSASSEMBLING_CODE + DISASSM_FCLOSE_ERROR;
        return;
    }
}