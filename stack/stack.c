#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||


#define STACK_ASSERT(stk) { \
    int status = StackStatus (&stk);                                    \
                                                                        \
    printf (#stk "(Status  -" (status == ALL_OK)?"OK\n)":"BROKEN\n)");  \
                                                                        \
    printf ("{");                                                       \
    printf ("size = %lu", stk.size);                                    \
                                                                        \
    if (stk.size < 0 or stk.size  > stk.capacity)                       \
        printf (" (WRONG)");                                            \
                                                                        \
    printf ("\n");                                                      \
                                                                        \
    printf ("capacity = %lu", stk.capacity);                            \
                                                                        \
    if (stk.capacity < 0)                                               \
        printf (" (WRONG)");                                            \
                                                                        \
    printf ("\n");                                                      \
                                                                        \
    printf ("data [%X]", stk.data);                                     \
                                                                        \
    if (stk.data == NULL)                                               \
        printf (" (WRONG)");                                            \
                                                                        \
    printf ("\n");                                                      \
                                                                        \
    if (status == ALL_OK)                                               \
        for (unsigned i = 0; i < stk.size; i++)                         \
            printf ("[%d] = %d", i, *(stack.data + i));                 \
                                                                        \
    printf ("\nCalled from line %d\n", __LINE__);                       \
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackConstructor (Stack* stack, size_t capacity)
{
    stack->data = (buff_type*) calloc (capacity, sizeof (*(stack->data)));

    stack->capacity = capacity;

    stack->size = 0;
    
    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackPush (Stack* stack, buff_type element)
{
    if (stack->size == stack->capacity)
    {
        stack->data = realloc (stack->data, stack->capacity * sizeof (*(stack->data)));
        stack->capacity *= 2;
    }

    stack->size += 1;

    stack->data[stack->size - 1] = element;

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

buff_type StackPop (Stack* stack)
{
    buff_type el = *(stack->data + stack->size);

    // TODO: придумать алгос чтобы адекватно уменьшать размер стэка

    stack->size -= 1;

    return el;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackStatus (Stack* stack)
{
    if (stack->data == NULL)
        return INCORRECT_DATA_POINTER;

    if (stack->size < 0)
        return INVALID_SIZE;

    if (stack->capacity < 0)
        return INVALID_CAPACITY;

    if (stack->size > stack->capacity)
        return INVALID_SIZE;

    return ALL_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StackDump (Stack stack, unsigned line_number)
{

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    Stack stack = {};
    StackConstructor (&stack, 10);
    StackPush (&stack, 10);
    STACK_ASSERT(stack);
}