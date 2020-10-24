#include "stack.c"

int main ()
{
    Stack stack = {};
    
    stack_type sym;

    StackCtor (&stack, 10);

    StackPush (&stack, 'f');
    
    StackDump (stack);

    StackPush (&stack, 'f');

    StackDump (stack);

    StackPop (&stack, &sym);

    StackDump (stack);

    printf ("%c\n", sym);
}