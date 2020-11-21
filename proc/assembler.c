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
    {{2, "in"},     0x22},
    {{4, "push"},   0x24},
    {{3, "mul"},    0x27},
    {{3, "add"},    0x29},
    {{3, "sub"},    0x42},
    {{3, "div"},    0x44},
    {{3, "out"},    0x47},
    {{3, "jmp"},    0x49},
    {{3, "hlt"},    0x99}
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
    ASSM_WHICHCOMMAND_CODE   = 2200,
    ASSM_TYPEOFINPUT_CODE    = 2400,
    ASSM_ASSEMBLING_CODE     = 2700
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const char delim[] = " \n";

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define CheckExitCode() assert(assm_exit_code == NO_EXCEPTIONS_ASSM);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned typeOfInput        (string s, double* number, string label_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assembling             (char* code_file, char* code_copy, string* str1, 
                            label* labels, long int label_number, 
                            long int count_str);

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
    label* labels = (label*)  calloc (1, sizeof (label));

    long int label_number = 0;

    labels[0].label_name.start = NULL;
    labels[0].label_name.len   = 0;
    labels[0].pointer          = 0;

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

    Assembling (code_file, code_copy, pointers_to_str, labels, label_number, count_str);

    Assembling (code_file, code_copy, pointers_to_str, labels, label_number, count_str);

    printf ("Assembling succesfull\n");

    free (code_copy);
    free (pointers_to_str);
    free (labels);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned typeOfInput (string s, double* number, string label_name)
{
    assert (s.start != NULL);

    unsigned res = 0;

    char* lexem = strtok (s.start, delim);

    string tmp = {strlen (lexem), lexem};

    for (int i = 0; i < tmp.len; ++i)
    {
        if (isalpha (tmp.start[i]))
        {
            if (res == 0 or res == ASSM_COMMAND_CODE)
                res = ASSM_COMMAND_CODE;

            else if (res != ASSM_LABEL_CODE)
            {
                res = ASSM_ERROR_CODE;
                assm_exit_code = ASSM_TYPEOFINPUT_CODE + ASSM_INPUT_EXCEPTION;
                return res;
            }
        }

        else if (isdigit (tmp.start[i]))
        {
            if (res != ASSM_LABEL_CODE)
            {
                res = ASSM_ERROR_CODE;
                assm_exit_code = ASSM_TYPEOFINPUT_CODE + ASSM_INPUT_EXCEPTION;
                return res;
            }
        }

        else if (tmp.start[i] == ':')
        {
            if (res == 0)
                res = ASSM_LABEL_CODE;
            else
            {
                res = ASSM_ERROR_CODE;
                assm_exit_code = ASSM_TYPEOFINPUT_CODE + ASSM_INPUT_EXCEPTION;
                return res;
            }
        }
        
        else
        {
            res = ASSM_ERROR_CODE;
            assm_exit_code = ASSM_TYPEOFINPUT_CODE + ASSM_INPUT_EXCEPTION;
            return res;            
        }
    }

    if (res == ASSM_COMMAND_CODE)
    {
        for (unsigned i = 0; i < number_commands; ++i)
            if (StrCompare (&tmp, &commands[i].text) == 0)
            {
                res += commands[i].code;
                break;
            }

        printf ("%x\n", res);

        if (res % 256 ==  commands[1].code)             //"push" command code
        {
            lexem = strtok (NULL, delim);

            sscanf (lexem, "%lf", number);

            char* tmp_for_copy = (char*) calloc (strlen (lexem), sizeof (char));

            strcpy (tmp_for_copy, lexem);

            strcat (s.start, " ");
            strcat (s.start, tmp_for_copy);

            free (tmp_for_copy);
        }

        if (res % 256 == commands[7].code)              //"jmp" command code
        {
            lexem = strtok (NULL, delim);

            char* tmp_for_copy = (char*) calloc (strlen (lexem), sizeof (char));

            strcpy (tmp_for_copy, lexem);

            if (tmp_for_copy[strlen (lexem) - 1] == ':')
            {
                tmp_for_copy[strlen (lexem) - 1] = '\0';
            }

            else
            {
                res = ASSM_ERROR_CODE;
                assm_exit_code = ASSM_INPUT_EXCEPTION + ASSM_TYPEOFINPUT_CODE;
                return res;
            }

            label_name.start = (char*) realloc (label_name.start, sizeof (char) * strlen (tmp_for_copy));
            label_name.len = strlen (tmp_for_copy);

            strcpy (label_name.start, tmp_for_copy);

            strcpy (tmp_for_copy, lexem);
            
            strcat (s.start, " ");
            strcat (s.start, tmp_for_copy);

            free (tmp_for_copy);      
        }
    }

    if (res == ASSM_LABEL_CODE)
    {
        if (lexem[0] == ':')
        {
            label_name.start = (char*) realloc (label_name.start, sizeof (char) * strlen (lexem + 1));
            label_name.len   = strlen (lexem + 1); 

            strcpy (label_name.start, lexem + 1);
        }

        else
        {
            res = ASSM_ERROR_CODE;
            assm_exit_code = ASSM_INPUT_EXCEPTION + ASSM_TYPEOFINPUT_CODE;
            return res;
        }
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assembling (char* code_file, char* code_copy, string* str1, 
                label* labels, long int label_count, long int count_str)
{
    assert (code_file);
    assert (code_copy);

    FILE* f = fopen (code_file, "wb");

    if (f == NULL)
    {
        assm_exit_code = ASSM_FOPEN_ERROR + ASSM_ASSEMBLING_CODE;
        return;
    }

    char* lexem = NULL;

    int prog_status = 1;
    int input = -1;
    int first_half = -1;
    int second_half = -1;

    double number = 0;

    string label_name = {1, (char*) calloc (1, sizeof (char))};

    for (long int i = 0; i < count_str and prog_status; ++i)
    {
        input = typeOfInput (str1[i], &number, label_name);

        printf ("%x %lf %s\n", input, number, label_name.start);

        first_half = input / 256 * 256;
        second_half = input % 256;

        CheckExitCode();

        switch (first_half)
        {
            case ASSM_COMMAND_CODE:
                CheckExitCode();

                if (second_half != commands[7].code)
                    fwrite (&second_half, sizeof (int), 1, f);

                if (second_half == commands[1].code)    //"push" command code
                    fwrite (&number, sizeof (double), 1, f);
                
                if (second_half == commands[7].code)    //"jmp" command code
                {
                    int label_number = -1;

                    for (int j = 0; j < label_count; ++j)
                        if (StrCompare (&label_name, &(labels[i].label_name)) == 0)
                        {
                            label_number = j;
                            break;
                        }
                        
                    if (labels[label_number].pointer != -1)
                        i = labels[label_number].pointer;
                }

                break;

            case ASSM_LABEL_CODE:
                labels[label_count].label_name = label_name;
                labels[label_count].pointer    = i;

                ++label_count;

                labels = (label*) realloc (labels, sizeof (label) * (label_count + 1));

                if (labels == NULL)
                {
                    assm_exit_code = ASSM_ASSEMBLING_CODE + ASSM_ALLOCATION_ERROR;
                    prog_status = 0;
                }

                break;

            default:
                assm_exit_code = ASSM_ASSEMBLING_CODE + ASSM_INPUT_EXCEPTION;
                prog_status = 0;
                break;
        }
    }

    if (fclose (f) != 0)
    {
        assm_exit_code = ASSM_ASSEMBLING_CODE + ASSM_FCLOSE_ERROR;
        return;
    }

    free (label_name.start);
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