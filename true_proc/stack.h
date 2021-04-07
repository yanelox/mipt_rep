//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Stack-type
*/
typedef double stack_type;
#define STACK_PRINT_TYPE "%lg"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief  Posion. If element have this value, it is incorrect. Macto POISON_EXIST 
            talking about existing POISON for this type of stack
*/
double POISON = NAN;
#define POISON_EXIST

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief  It's define a macro to check values for POISON taking into account existing 
            of POISON
*/
#ifdef POISON_EXIST
#define HARD_CHECK_FOR_POISON(el) assert ((el) != POISON);
#else 
#define HARD_CHECK_FOR_POISON(el) ;
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Variable which store message about errors
*/
extern int stack_exit_code;

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
    STACK_CTOR_CODE       = 1,    //Code of StackCtor()
    STACK_PUSH_CODE       = 2,    //Code of StackPush()
    STACK_POP_CODE        = 3,    //Code of StackPop()
    STACK_VALIDATY_CODE   = 4,    //Code of StackValidaty()
    STACK_INCREASE_CODE   = 5,    //Code of StackIncrease()
    STACK_DECREASE_CODE   = 6,    //Code of StackDecrease()
    STACK_DUMP_CODE       = 7     //Code of macro StackDump()
};

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

    @param [in] stack   Pointer to stack where from we want to take element

    @return             Returns taken from stack element
*/
stack_type StackPop         (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Function which check stack for correctness

    @param [in] stack       Stack which we want to check
    @param [in] func_code   Number of func (from FunctionNumbers) where was called this func

    @return 1, if all correct, 0 if there are some exceptions

    @note   Write exception code to stack_exit_code value
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

    @return             Calculated value of hash_sum
*/
unsigned long long HashSum  (Stack stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which print info about exception using exception code 
            which stored in stack_exit_code variable
*/

void Stack_PrintExitCode ();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief Function which print all necessary info about stack

    @param [in] stack       Stack which info you want print about
    @param [in] func_name   Name of function where we called StackDumpF()
    @param [in] line_number Line number where was called StackDumpF()
    @param [in] file_name   Name of file whre was called StackDumpF()
    @param [in] stack_name  String which contents real name of stack variable

    @note There is StackDump macro below for more simple using  
*/
void StackDumpF             (Stack stack, const char* func_name, int line_number, 
                            const char* file_name, const char* stack_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*!
    \brief  Macro which called StackDumpF() but automatically paste parametres func_name,
            line_number, file_name, stack_name using system macros
*/
#define StackDump(stack) StackDumpF (stack, __PRETTY_FUNCTION__, __LINE__, \
                                    __FILE__, #stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void UnitTest               ();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx