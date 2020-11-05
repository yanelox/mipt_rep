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
    IN_CODE     =   22,
    PUSH_CODE   =   24,
    MUL_CODE    =   27,
    ADD_CODE    =   29,
    SUB_CODE    =   42,
    DIV_CODE    =   44,
    OUT_CODE    =   47,
    HLT_CODE    =   49
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const char delim[] = " \n";

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int RunProg (char* code_copy);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char* argv[])
{
    Stack stack;
    StackCtor (&stack, 10);

    char* code_file = argv[1];
    char* code_copy = NULL;

    long int count_sym = CountSymbols (code_file);

    code_copy = (char*) calloc (count_sym, sizeof (char));
    FromFileToStr (code_file, code_copy, count_sym);

    RunProg (code_copy);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int RunProg (char* code_copy)
{   
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
            case IN_CODE:
                scanf (STACK_PRINT_TYPE, &input_value);
                StackPush (&stack, input_value);
                break;

            case PUSH_CODE:
                sscanf (code_copy, STACK_PRINT_TYPE"%n", &input_value, &shift);
                code_copy += shift;

                StackPush (&stack, input_value);
                break;

            case MUL_CODE:
                tmp1 = StackPop (&stack);
                tmp2 = StackPop (&stack);
                tmp1 *= tmp2;

                StackPush (&stack, tmp1);
                break;

            case ADD_CODE:
                tmp1 = StackPop (&stack);
                tmp2 = StackPop (&stack);
                tmp1 += tmp2;

                StackPush (&stack, tmp1);
                break;

            case SUB_CODE:
                tmp1 = StackPop (&stack);
                tmp2 = StackPop (&stack);
                tmp2 -= tmp1;
                
                StackPush (&stack, tmp2);
                break;

            case DIV_CODE:
                tmp1 = StackPop (&stack);
                tmp2 = StackPop (&stack);
                tmp2 /= tmp1;

                StackPush (&stack, tmp2);
                break;

            case OUT_CODE:
                tmp1 = StackPop (&stack);
                printf (STACK_PRINT_TYPE "\n", tmp1);

                break;

            case HLT_CODE:
                prog_status = 0;

                break;

            default:
                prog_status = 0;

                break;
        }
    }
}