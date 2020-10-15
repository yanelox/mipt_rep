typedef int buff_type;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct 
{
    buff_type* data;

    size_t size;

    size_t capacity;
} 
Stack;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum ReturnedValues
{
    ALL_OK = 0xCAFEBABE,

    INCORRECT_DATA_POINTER = 0x8BADD00D,

    INVALID_SIZE = 0x8BADBABE,

    INVALID_CAPACITY = 0xCAFED00D
};