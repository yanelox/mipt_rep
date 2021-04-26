#include "special_onegin.h"
#pragma once

typedef struct
{
    string label_name = {0, nullptr};

    long int pointer = 0;

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
    {{2,(char*) "in"},     0x11},
    {{4,(char*) "push"},   0x12}, 
    {{4,(char*) "push"},   0x13},  
    {{3,(char*) "pop"},    0x14},  // pop to register
    {{3,(char*) "mul"},    0x16},
    {{3,(char*) "add"},    0x17},
    {{3,(char*) "sub"},    0x18},
    {{3,(char*) "div"},    0x19},
    {{3,(char*) "out"},    0x20},
    {{3,(char*) "jmp"},    0x21},
    {{3,(char*) "sin"},    0x22},
    {{3,(char*) "cos"},    0x23},
    {{4,(char*) "sqrt"},   0x24},
    {{3,(char*) "hlt"},    0x99}       //TODO: add conditional jumps(ja >),(jae >=),(jb <),(jbe <=),(je ==),(jne !=)
};

const size_t number_commands = 14;  

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
    ASSM_ALLOCATION_ERROR   = 42,
    ASSM_PUSH_ARG_ERROR     = 44
};

int assm_exit_code = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum assm_func_codes
{
    ASSM_WHICHCOMMAND_CODE      = 2200,
    ASSM_DECRYPTINPUT_CODE      = 2400,
    ASSM_ASSEMBLING_CODE        = 2700,
    ASSM_STARTASSM_CODE         = 2900
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const char delim[] = " \n";

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define CheckExitCode() assert(assm_exit_code == NO_EXCEPTIONS_ASSM);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assembling             (string* str, long int count_str, char* code_file, 
                            label** labels, long int* label_count, FILE* log_file);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int Decrypt_Input           (string str, label** labels, long int* label_count, 
                            double* ret_v, long int cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LabelFree              (label* labels, long int label_count);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assm_PrintExitCode     (char* file_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StartAssembling        (int argc, char* argv[]);