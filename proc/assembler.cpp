#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "special_onegin.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct
{
    string label_name;

    long int pointer;

} label;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct
{
    string text;

    int code;

} Command;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Command commands[] =
{
    {{2, (char*) "in"},     0x22},
    {{4, (char*) "push"},   0x24},
    {{3, (char*) "mul"},    0x27},
    {{3, (char*) "add"},    0x29},
    {{3, (char*) "sub"},    0x42},
    {{3, (char*) "div"},    0x44},
    {{3, (char*) "out"},    0x47},
    {{3, (char*) "jmp"},    0x49},
    {{3, (char*) "hlt"},    0x99}
};

const size_t number_commands = 9;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum assm_input_types
{
    ASSM_COMMAND_CODE    = 0x2200,
    ASSM_LABEL_CODE      = 0x2400,
    ASSM_ERROR_CODE      = 0x9900
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum assm_exit_codes
{
    NO_EXCEPTIONS_ASSM      = 00,
    ASSM_INCORRECT_COMMAND  = 22,
    ASSM_INPUT_EXCEPTION    = 24,
    ASSM_FOPEN_ERROR        = 27,
    ASSM_FCLOSE_ERROR       = 29,
    ASSM_ALLOCATION_ERROR   = 42
};

int assm_exit_code = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum assm_func_codes
{
    ASSM_WHICHCOMMAND_CODE      = 2200,
    ASSM_DECRYPTINPUT_CODE      = 2400,
    ASSM_ASSEMBLING_CODE        = 2700
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const char delim[] = " \n";

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define CheckExitCode() assert(assm_exit_code == NO_EXCEPTIONS_ASSM);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assembling             (string* str, long int count_str, char* code_file, 
                            label** labels, long int* label_count);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int Decrypt_Input           (string str, label** labels, long int* label_count, 
                            double* ret_v, long int cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LabelFree              (label* labels, long int label_count);

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
    long int count_str = 0;

    string* pointers_to_str = (string*) calloc (count_str, sizeof (string)); 

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

    if (FromFileToStr (assm_file, code_copy, count_sym) == -1)
    {
        Onegin_PrintExitCode();
        return 0;
    }

    count_str = CountStr (code_copy);

    FillPMassive (pointers_to_str, code_copy, count_str, count_sym);

    // label* labels = (label*)  calloc (1, sizeof (label));

    // long int label_count = 0;

    // labels[0].label_name.start = NULL;
    // labels[0].label_name.len   = 0;
    // labels[0].pointer          = 0;

    // Assembling (pointers_to_str, count_str, code_file, &labels, &label_count);
    // Assembling (pointers_to_str, count_str, code_file, &labels, &label_count);

    // FILE* f = fopen (code_file, "wb");
    // printf ("%p\n", f);
    // fclose (f);

    PrintStr (pointers_to_str, count_str);
    printf ("%u\n", pointers_to_str[1].len);

    // printf ("Assembling succesfull\n");

    // free (code_copy);
    // free (pointers_to_str);
    // LabelFree (labels, label_count);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assembling (string* str, long int count_str, char* code_file, label** labels, long int* label_count)
{
    assert (str);
    assert (labels);
    assert (*labels);
    assert (code_file);

    int res = -1;
    double ret_v = -1;

    FILE* f = fopen (code_file, "wb");

    printf ("%p\n", f);

    // if (f == NULL)
    // {
    //     assm_exit_code = ASSM_ASSEMBLING_CODE + ASSM_ALLOCATION_ERROR;
    //     return;
    // }

    // for (long int i = 0; i < count_str; ++i)
    // {
    //     ret_v = -1;
    //     res = -1;

    //     printf ("%ld 1\n", i);

    //     // res = Decrypt_Input (str[i], labels, label_count, &ret_v, i);

    //     if (res == -1)
    //     {
    //         break;
    //     }

    //     if (res / 256 * 256 == ASSM_COMMAND_CODE)
    //     {
    //         int half_res = res % 256;

    //         if (half_res == commands[1].code) //push code
    //         {
    //             fwrite (&half_res, sizeof (int), 1, f);
    //             fwrite (&ret_v, sizeof (double), 1, f);
    //         }

    //         else if (half_res == commands[7].code)
    //         {
    //             if (ret_v != -1)
    //                 i = ret_v - 1;
    //         }
            
    //         else
    //         {
    //             fwrite (&half_res, sizeof (int), 1, f);
    //         }
    //     }

    //     printf ("%ld 2\n", i);
    // }

    fclose (f);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int Decrypt_Input (string str, label** labels, long int* label_count, double* ret_v, long int cur_p)
{
    assert (str.start);
    assert (labels);
    assert (*labels);
    assert (label_count);
    assert (ret_v);

    char delim[] = " \n";

    char* lexem = strtok (str.start, delim);

    string first_part = StrCtor (strlen (lexem), lexem);

    unsigned num = -1;

    if (first_part.start[0] == ':')
    {
        (*label_count)++;

        *labels = (label*) realloc (*labels, sizeof (label) * (*label_count + 1));

        (*labels)[*label_count - 1].label_name = StrCtor (first_part.len, first_part.start + 1);
        (*labels)[*label_count - 1].pointer    = cur_p;

        return ASSM_LABEL_CODE;
    }

    for (unsigned i = 0; i < number_commands; ++i)
    {
        if (!StrCompare (&(commands[i].text), &first_part))
        {
            num = i;
            break;
        }
    }

    if (num == -1)
    {
        assm_exit_code = ASSM_DECRYPTINPUT_CODE + ASSM_INPUT_EXCEPTION;
        return -1;
    }

    if (num == 1) //push code
    {
        int res = sscanf (str.start + first_part.len + 1, "%lf", ret_v);

        if (res != 1)
        {
            assm_exit_code = ASSM_DECRYPTINPUT_CODE + ASSM_INPUT_EXCEPTION;
            return -1;
        }
    }

    if (num == 7)   //jmp code
    {
        lexem = strtok (str.start + first_part.len + 1, delim);

        string second_part = StrCtor (strlen (lexem), lexem);

        for (long int i = 0; i < *label_count; ++i)
        {
            if (!StrCompare (&second_part, &(commands[i].text)))
            {
                *ret_v = i;
                break;
            }
        }

        StrDtor (second_part);
    }

    strcat (str.start, first_part.start + first_part.len + 1);

    return ASSM_COMMAND_CODE + commands[num].code;
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

        case ASSM_DECRYPTINPUT_CODE:
            printf ("DecryptInput() ");
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

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LabelFree (label* labels, long int label_count)
{
    assert (labels);

    for (long int i = 0; i < label_count; ++i)
    {
        StrDtor (labels[i].label_name);
        labels[i].pointer = 0;
    }

    free (labels);
}