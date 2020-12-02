//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define ReadNode_Save_Error(statement) \
{                                                               \
    if (!(statement))                                           \
    {                                                           \
        diff_exit_code = DIFF_INCORRECT_SAVE + DIFF_READNODE;   \
                                                                \
        return (TreeEl*) NULL;                                  \
    }                                                           \
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

extern int diff_exit_code;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum diff_exit_codes
{
    DIFF_NO_EXCEPTIONS      = 0x00,
    DIFF_ALLOCATION_ERROR   = 0x22,
    DIFF_INCORRECT_SAVE     = 0x24,
    DIFF_FILEOPEN_ERROR     = 0x27
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum diff_func_codes
{
    DIFF_TREECTOR       = 0x2200,
    DIFF_READNODE       = 0x2400,
    DIFF_STARTREADING   = 0x2700
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum diff_data_types
{
    DIFF_OPERATION_TYPE = 0x22,
    DIFF_NUMBER_TYPE    = 0x24,
    DIFF_VARIABLE_TYPE  = 0x27
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum diff_operators_codes
{
    DIFF_SUM    = 0x22,
    DIFF_MUL    = 0x24,
    DIFF_DIV    = 0x27,
    DIFF_SUB    = 0x29,
    DIFF_POW    = 0x42,
    DIFF_LN     = 0x44,
    DIFF_COS    = 0x47,
    DIFF_SIN    = 0x49
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct el
{
    int type;

    int value;

    el* prev;

    el* left;
    el* right;
};

typedef struct el TreeEl;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* TreeCtor            (int type, int value, el* prev);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int isoperation             (char sym);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char GetOperation           (int num);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* ReadNode            (TreeEl* prev, char** source);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* StartReading        (char* source);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintTree              (TreeEl* tree);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TreeDtor               (TreeEl* tree);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* CopyNode            (TreeEl* source, TreeEl* prev);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* DiffTree            (TreeEl* tree, TreeEl* prev);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* TreeSimplification  (TreeEl* tree, TreeEl* prev);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void SaveNodeL              (TreeEl* tree, FILE* doc);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StartLSaving           (TreeEl* tree, FILE* doc);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void MakeLFile              (TreeEl* tree, TreeEl* diff_tree, char* file_name);