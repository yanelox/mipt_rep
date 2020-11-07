#include <stdio.h>
#include <string.h>
#include "stack.c"
#include "special_onegin.c"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum commands
{
    CPU_IN_CODE     =   22,
    CPU_PUSH_CODE   =   24,
    CPU_MUL_CODE    =   27,
    CPU_ADD_CODE    =   29,
    CPU_SUB_CODE    =   42,
    CPU_DIV_CODE    =   44,
    CPU_OUT_CODE    =   47,
    CPU_HLT_CODE    =   49
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const char delim[] = " \n";

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int RunProg (char* code_copy);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        printf ("Incorrect arguments");
        return 0;
    }

    char* code_file = argv[1];
    char* code_copy = NULL;

    long int count_sym = CountSymbols (code_file);

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

    RunProg (code_copy);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int RunProg (char* code_copy)
{   
    Stack stack;
    StackCtor (&stack, 10);

    if (stack_exit_code != NO_EXCEPTIONS)
    {
        Stack_PrintExitCode ();
        return 0;
    }

    int tmp = 0;
    int shift = 0;

    int prog_status = 1;

    stack_type input_value = 0;
    stack_type tmp1 = 0;
    stack_type tmp2 = 0;

    while (prog_status)
    {
        sscanf (code_copy, "%d%n", &tmp, &shift);

        code_copy += shift;

        switch (tmp)
        {
            case CPU_IN_CODE:
                scanf (STACK_PRINT_TYPE, &input_value);
                StackPush (&stack, input_value);
                break;

            case CPU_PUSH_CODE:
                sscanf (code_copy, STACK_PRINT_TYPE"%n", &input_value, &shift);
                code_copy += shift;

                StackPush (&stack, input_value);
                break;

            case CPU_MUL_CODE:
                tmp1 = StackPop (&stack);
                tmp2 = StackPop (&stack);
                tmp1 *= tmp2;

                StackPush (&stack, tmp1);
                break;

            case CPU_ADD_CODE:
                tmp1 = StackPop (&stack);
                tmp2 = StackPop (&stack);
                tmp1 += tmp2;

                StackPush (&stack, tmp1);
                break;

            case CPU_SUB_CODE:
                tmp1 = StackPop (&stack);
                tmp2 = StackPop (&stack);
                tmp2 -= tmp1;
                
                StackPush (&stack, tmp2);
                break;

            case CPU_DIV_CODE:
                tmp1 = StackPop (&stack);
                tmp2 = StackPop (&stack);
                tmp2 /= tmp1;

                StackPush (&stack, tmp2);
                break;

            case CPU_OUT_CODE:
                tmp1 = StackPop (&stack);
                printf (STACK_PRINT_TYPE "\n", tmp1);

                break;

            case CPU_HLT_CODE:
                prog_status = 0;

                break;

            default:
                prog_status = 0;

                break;
        }
    }
}