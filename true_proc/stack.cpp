#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "stack.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int stack_exit_code = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StackCtor (Stack* stack, size_t capacity)
{
    assert (stack != NULL);
    assert (capacity > 0);

    stack_type* tmp_start = (stack_type*) calloc (capacity, sizeof (stack_type));

    if (tmp_start == NULL)
    {
        stack_exit_code = MEMORY_ALLOC_ERROR + STACK_CTOR_CODE;
        return;
    }

    stack->StartBird = HUMMINGBIRD;
    stack->start = tmp_start;
    stack->size = 0;
    stack->capacity = capacity;
    stack->hash = HashSum (*stack);
    stack->EndBird = HUMMINGBIRD;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StackPush (Stack* stack, stack_type new_el)
{
    assert (stack != NULL);
    HARD_CHECK_FOR_POISON (new_el);

    if (!StackValidity (*stack, STACK_PUSH_CODE)) 
        return;

    if (!StackIncrease (stack)) //If Increase is impossible we can't add new element to stack
        return;

    stack->size += 1;

    *(stack->start + stack->size - 1) = new_el;

    stack->hash = HashSum (*stack);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

stack_type StackPop (Stack* stack)
{
    assert (stack != NULL);

    if (!StackValidity (*stack, STACK_POP_CODE))
        return -1;

    stack_type returned_value = *(stack->start + stack->size - 1);

    StackDecrease (stack);

    *(stack->start + stack->size - 1) = 0;

    stack->size -= 1;

    stack->hash = HashSum (*stack);

    return returned_value;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackValidity (Stack stack, const int func_code)
{
    if (stack.start == NULL)
    {
        stack_exit_code = INCORRECT_STACK_POINTER + func_code;
        return 0;
    }

    if (stack.size > stack.capacity or stack.size < 0)
    {
        stack_exit_code = INCORRECT_STACK_SIZE + func_code;
        return 0;
    }

    if (stack.capacity < 0)
    {
        stack_exit_code = INCORRCT_STACK_CAPACITY + func_code;
        return 0;
    }

    if (stack.StartBird != HUMMINGBIRD)
    {
        stack_exit_code = WRONG_START_HUMMINGBIRD + func_code;
        return 0;
    }

    if (stack.EndBird != HUMMINGBIRD)
    {
        stack_exit_code = WRONG_END_HUMMINGBIRD + func_code;
        return 0;
    }

    if (stack.hash != HashSum (stack))
    {
        stack_exit_code = WRONG_HASH_SUM + func_code;
        return 0;
    }
    
    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackIncrease (Stack* stack)
{
    assert (stack != NULL);

    if (!StackValidity (*stack, STACK_INCREASE_CODE))
        return 0;
    
    if (stack->size + 1 > stack->capacity) 
    {
        void* res_pointer = realloc (stack->start, 2 * stack->capacity * sizeof (stack_type));
        
        if (res_pointer == NULL)
        {
            stack_exit_code = MEMORY_ALLOC_ERROR + STACK_INCREASE_CODE; 
            return 0;
        }
        
        stack->capacity *= 2;

        stack->start = (stack_type*) res_pointer;
    } 

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDecrease (Stack* stack)
{
    assert (stack != NULL);

    if (!StackValidity (*stack, STACK_DECREASE_CODE))
        return 0;

    if (2 * (stack->size - 1) < stack->capacity) 
    {
        void* res_pointer = realloc     (stack->start,              
                                        stack->capacity * sizeof (stack_type) * 2 / 3   //Decrease stack capacity by ~1.5 times
                                        + sizeof (stack_type));

        if (res_pointer == NULL)
        {
            stack_exit_code = MEMORY_ALLOC_ERROR + STACK_DECREASE_CODE;
            return 0;
        }

        stack->capacity = stack->capacity / 3 * 2 + 1;

        stack->start = (stack_type*) res_pointer;
    }

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned long long HashSum (Stack stack)
{
    unsigned long long res = 0;

    for (unsigned i = 0; i < stack.size; i++)
    {
        res += stack.start[i];

        res = res << sizeof (stack_type);
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Stack_PrintExitCode ()
{
    int tmp = stack_exit_code / 256 * 256;

    if (tmp == NO_EXCEPTIONS)
    {
        printf ("No errors founded\n");
        return;
    }

    switch (tmp)
    {
        case MEMORY_ALLOC_ERROR:
            printf ("Memory allocation error in ");
            break;
    
        case INCORRECT_STACK_POINTER:
            printf ("Incorrect pointer to start of buffer founded in ");
            break;

        case INCORRECT_STACK_SIZE:
            printf ("Stack size below zero or stack overdlow exception founded in ");
            break;

        case INCORRCT_STACK_CAPACITY:
            printf ("Stack capacity below zeor  founded in ");
            break;

        case WRONG_START_HUMMINGBIRD:
            printf ("Changes in start hummingbird founded in ");
            break;

        case WRONG_END_HUMMINGBIRD:
            printf ("Changes in end hummingbird founded in ");
            break;

        case WRONG_HASH_SUM:
            printf ("Mismacth of hash sum founded in ");
            break;

        default:
            printf ("Unkwonw exception with number %X in ", tmp);
            break;
    }

    tmp = stack_exit_code % 256;

    switch (tmp)
    {
        case STACK_CTOR_CODE:
            printf ("func StackCtor()\n");
            break;

        case STACK_PUSH_CODE:
            printf ("func StackPush()\n");
            break;

        case STACK_POP_CODE:
            printf ("func StackPop()\n");
            break;

        case STACK_INCREASE_CODE:
            printf ("func StackIncrease()\n");
            break;

        case STACK_DECREASE_CODE:
            printf ("func StackDecrease()\n");
            break;

        case STACK_DUMP_CODE:
            printf ("macro StackDump()\n");
            break;

        default:
            printf ("unkwonw func with number %X\n", tmp);
            break;
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StackDumpF (Stack stack, const char* func_name, int line_number, const char* file_name, const char* stack_name)
{                                                   
    int check = StackValidity (stack, STACK_DUMP_CODE);   
                                                    
    if (check == 1)                                 
        printf ("Stack[OK]: ");          
    else                                           
        printf ("Stack[WRONG][CODE: %d]: ", stack_exit_code);                  
                                                    
    printf ("[%p] ", stack.start);

    printf ("\"%s\" %s line %d %s", stack_name, func_name, line_number, file_name);

    printf ("\n{\n");              
                                                
    printf ("size = %lu \n", stack.size);           
                                                    
    printf ("capacity = %lu\n", stack.capacity);    
                                                    
    printf ("hash_sum = %llX\n", stack.hash);       
                                                    
    printf ("   {\n");                              
                                                    
    for (size_t i = 0; i < stack.capacity; i++)     
    {                                               
        printf ("   ");                             
        if (i < stack.size)                        
            printf  ("*");                          
        else                                        
            printf (" ");                           
        printf  ("[%lu\t] = " STACK_PRINT_TYPE "\n", i, stack.start[i]);                
    }                                               
                                                    
    printf ("   }\n}\n");                           
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void UnitTest ()
{
    Stack stack1 = {};
    Stack stack2 = {};
    Stack stack3 = {};

    char test1[] = "PRESS F TO PAY RESPECTS";
    char test2[] = "HAHA OFIGENNO";
    char test3[] = "42 or 97 hmmmmmmmm";

    StackCtor (&stack1, 50);
    StackCtor (&stack2, 50);
    StackCtor (&stack3, 50);

    for (int i = 0; test1[i]; i++)
        StackPush (&stack1, test1[i]);

    for (int i = 0; test2[i]; i++)
        StackPush (&stack2, test2[i]);

    for (int i = 0; test3[i]; i++)
        StackPush (&stack3, test3[i]);

    StackDump (stack1);
    StackDump (stack2);
    StackDump (stack3);
}