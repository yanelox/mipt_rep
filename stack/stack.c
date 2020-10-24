#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief  Posion. If element have this value, it is incorrect. Macto POISON_EXIST 
            talking about existing POISON for this type of stack
*/
double POISON = NAN;
//#define POISON_EXIST

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief  It's define a macro to check values for POISON taking into account existing 
            of POISON
*/
#ifdef POISON_EXIST
#define HARD_CHECK_FOR_POISON(el) assert ((el) != POISON);
#else 
#define HARD_CHECK_FOR_POISON(el)
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Variable which store message about errors
*/
int exit_code = 0;

/*!
    \brief Codes of exceptions
    
*/
enum ExitCodes
{
    NO_EXCEPTIONS               = 0x000000, //If all is OK
    MEMORY_ALLOC_ERROR          = 0x222200, //Error while allocation memory in functions calloc/realloc
    INCORRECT_STACK_POINTER     = 0x222400, //Incorrect pointer to start of stack buffer
    INCORRECT_STACK_SIZE        = 0x222700, //Size below zero or size more than capacity
    INCORRCT_STACK_CAPACITY     = 0x222900, //Capacity below zero
    WRONG_START_HUMMINGBIRD     = 0x224200, //Changes in start-hummingbird
    WRONG_END_HUMMINGBIRD       = 0x224400, //Changes in end-hummingbird
    WRONG_HASH_SUM              = 0x224700  //Mismath with recorded hash-sum
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum FunctionNumbers
{
    CTOR_CODE       = 1,    //Code of StackCtor()
    PUSH_CODE       = 2,    //Code of StackPush()
    POP_CODE        = 3,    //Code of StackPop()
    VALIDATY_CODE   = 4,    //Code of StackValidaty()
    INCREASE_CODE   = 5,    //Code of StackIncrease()
    DECREASE_CODE   = 6,    //Code of StackDecrease()
    DUMP_CODE       = 7     //Code of macro StackDump()
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Macro which print all info about stack

    @param [in] stack Stack-type variable, which info we want to print about
*/

#define StackDump(stack) \
{                                                   \
    int check = StackValidity (stack, DUMP_CODE);   \
                                                    \
    if (check == 1)                                 \
        printf ("Stack[OK]: " #stack " ");          \
    else                                            \
        printf ("Stack[WRONG][CODE: %d]:            \
        " #stack " ", exit_code);                   \
                                                    \
    printf ("[%p]\n{\n", stack.start);              \
                                                    \
    printf ("size = %lu \n", stack.size);           \
                                                    \
    printf ("capacity = %lu\n", stack.capacity);    \
                                                    \
    printf ("hash_sum = %llX\n", stack.hash);       \
                                                    \
    printf ("   {\n");                              \
                                                    \
    for (size_t i = 0; i < stack.capacity; i++)     \
    {                                               \
        printf ("   ");                             \
        if (i < stack.size)                         \
            printf  ("*");                          \
        else                                        \
            printf (" ");                           \
        printf  ("[%lu] = %c\n", i,                 \
                *(stack.start + i));                \
    }                                               \
                                                    \
    printf ("   }\n}\n");                           \
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Stack-type
*/
typedef char stack_type;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Variable which control incorrect changes in stack
*/
typedef unsigned long long hummingbird_type;

/*!
    \brief True value of start and end hummingbirds in stack
*/
const hummingbird_type HUMMINGBIRD = (hummingbird_type) 0xBADDAD;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Struct which define stack-type and all it's variables
*/
typedef struct
{
    hummingbird_type StartBird;     //Start hummingbird

    stack_type* start;              //Pointer to start of buffer

    size_t size;                    //Count of eleemnts in buffer
    
    size_t capacity;                //Max count of elements in buffer

    unsigned long long hash;        //Hash sum of data in buffer

    hummingbird_type EndBird;       //End hummingbird

} Stack;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Function which define correct stack

    @param [in] stack       Pointer to stack which we want to construct
    @param [in] capacity    Max count of values in our stack
*/
void StackCtor              (Stack* stack, size_t capacity);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Function which add new element in stack

    @param [in] stack       Pointer to stack where we want to add
    @param [in] new_el      Element which we want to add
*/
void StackPush              (Stack* stack, stack_type new_el);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Fucntion which take last element from stack

    @param [in] stack               Pointer to stack where from we want to take element
    @param [in] returned_value_p    Pointer to value where we want to write value from stack
*/
void StackPop               (Stack* stack, stack_type* returned_value_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Function which check stack for correctness

    @param [in] stack       Stack which we want to check
    @param [in] func_code   Number of func (from FunctionNumbers) where was called this func

    @return 1, if all correct, 0 if there are some exceptions

    @note   Write exception code to exit_code value
*/
int StackValidity           (Stack stack, const int func_code);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Increase stack capacity if it is necessary

    @param [in] stack Stack which capacity we want to increase

    @note  Increase capacity by 2 times 
*/
int StackIncrease           (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Decrease stack capcity if it's possible

    @param [in] stack   Stack which capacity we want to decrease

    @note  If stack size 2 times less than capacity we decrease capacity by ~1.5 times  
*/
int StackDecrease           (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Calculate hash_sum of stack buffer

    @param [in] stack   Stack which hash_sum of buffer we want to caclulate

    @return      Calculated value of hash_sum
*/
unsigned long long HashSum  (Stack stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StackCtor (Stack* stack, size_t capacity)
{
    assert (stack != NULL);
    assert (capacity > 0);

    stack_type* tmp_start = (stack_type*) calloc (capacity, sizeof (stack_type));

    if (tmp_start == NULL)
    {
        exit_code = MEMORY_ALLOC_ERROR + CTOR_CODE;
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

    if (!StackValidity (*stack, PUSH_CODE)) 
        return;

    if (!StackIncrease (stack)) //If Increase is impossible we can't add new element to stack
        return;

    stack->size += 1;

    *(stack->start + stack->size - 1) = new_el;

    stack->hash = HashSum (*stack);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StackPop (Stack* stack, stack_type* returned_value_p)
{
    assert (returned_value_p != NULL);
    assert (stack != NULL);

    if (!StackValidity (*stack, POP_CODE))
        return;

    stack_type returned_value = *(stack->start + stack->size - 1);

    StackDecrease (*stack);

    *(stack->start + stack->size - 1) = '\0';

    stack->size -= 1;

    *returned_value_p = returned_value;

    stack->hash = HashSum (*stack);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackValidity (Stack stack, const int func_code)
{
    if (stack.start == NULL)
    {
        exit_code = INCORRECT_STACK_POINTER + func_code;
        return 0;
    }

    if (stack.size > stack.capacity or stack.size < 0)
    {
        exit_code = INCORRECT_STACK_SIZE + func_code;
        return 0;
    }

    if (stack.capacity < 0)
    {
        exit_code = INCORRCT_STACK_CAPACITY + func_code;
        return 0;
    }

    if (stack.StartBird != HUMMINGBIRD)
    {
        exit_code = WRONG_START_HUMMINGBIRD + func_code;
        return 0;
    }

    if (stack.EndBird != HUMMINGBIRD)
    {
        exit_code = WRONG_END_HUMMINGBIRD + func_code;
        return 0;
    }

    if (stack.hash != HashSum (stack))
    {
        exit_code = WRONG_HASH_SUM + func_code;
        return 0;
    }
    
    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackIncrease (Stack* stack)
{
    assert (stack != NULL);

    if (!StackValidity (*stack, INCREASE_CODE))
        return 0;
    
    if (stack->size + 1 > stack->capacity) 
    {
        void* res_pointer = realloc (stack->start, 2 * stack->capacity * sizeof (stack_type));
        
        if (res_pointer == NULL)
        {
            exit_code = MEMORY_ALLOC_ERROR + INCREASE_CODE; 
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

    if (!StackValidity (*stack, DECREASE_CODE))
        return 0;

    if (2 * (stack->size - 1) < stack->capacity) 
    {
        void* res_pointer = realloc     (stack->start,              
                                        stack->capacity * sizeof (stack_type) * 2 / 3   //Decrease stack capacity by ~1.5 times
                                        + sizeof (stack_type));

        if (res_pointer == NULL)
        {
            exit_code = MEMORY_ALLOC_ERROR + DECREASE_CODE;
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

void PrintExitCode ()
{
    int tmp = exit_code / 256 * 256;

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

    tmp = exit_code % 256;

    switch (tmp)
    {
        case CTOR_CODE:
            printf ("func StackCtor()\n");
            break;

        case PUSH_CODE:
            printf ("func StackPush()\n");
            break;

        case POP_CODE:
            printf ("func StackPop()\n");
            break;

        case INCREASE_CODE:
            printf ("func StackIncrease()\n");
            break;

        case DECREASE_CODE:
            printf ("func StackDecrease()\n");
            break;

        case DUMP_CODE:
            printf ("macro StackDump()\n");
            break;

        default:
            printf ("unkwonw func with number %X\n", tmp);
            break;
    }

    return;
}