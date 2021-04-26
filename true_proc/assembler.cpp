#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "special_onegin.h"
#include "assembler.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        printf("Incorrect arguments\n");
        return 0;
    }

    StartAssembling (argc, argv);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StartAssembling(int argc, char* argv[])
{
    char* assm_file = argv[1];
    char* code_file = argv[2];
    char* log_file  = argv[3];

    char* code_copy = NULL;

    long int count_sym = 0;
    long int count_str = 0;

    count_sym = CountSymbols(assm_file);

    if(count_sym == -1)
    {
        Onegin_PrintExitCode(log_file);
        return;
    }

    code_copy =(char*) calloc(count_sym, sizeof(char));

    if(code_copy == NULL)
    {
        assm_exit_code = ASSM_STARTASSM_CODE + ASSM_ALLOCATION_ERROR;
        Assm_PrintExitCode(log_file);
        return;
    }

    if(FromFileToStr(assm_file, code_copy, count_sym) == -1)
    {
        Onegin_PrintExitCode(log_file);
        return;
    }

    count_str = CountStr(code_copy);

    string* pointers_to_str = NULL; 

    pointers_to_str =(string*) calloc(count_str, sizeof(string));

    FillPMassive(pointers_to_str, code_copy, count_str, count_sym);

    label* labels =(label*)  calloc(1, sizeof(label));

    long int label_count = 0;

    FILE* log = NULL;

    if (strlen(log_file) == 2 and log_file[0] == '-' and log_file[1] == 'c')
        log = stdout;

    else
        log = fopen(log_file, "w");

    fprintf(log ,"First step starting:\n");

    Assembling(pointers_to_str, count_str, code_file, &labels, &label_count, log);

    fprintf(log, "First step succesfully completed.\nSecond step starting:\n");

    Assembling(pointers_to_str, count_str, code_file, &labels, &label_count, log);
    
    fprintf(log, "Second step succesfully completed.\n");

    fprintf(log,"Assembling succesfull\n");

    fclose(log);

    free(pointers_to_str);
    LabelFree(labels, label_count);
    free(code_copy);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assembling(string* str, long int count_str, char* code_file, label** labels, long int* label_count, FILE* log_file)
{
    assert(str);
    assert(labels);
    assert(*labels);
    assert(code_file);

    int res = -1;
    double ret_v = -1; //TODO: добавить интовский ретв

    FILE* f = fopen(code_file, "wb");

    if(f == NULL)
    {
        assm_exit_code = ASSM_ASSEMBLING_CODE + ASSM_ALLOCATION_ERROR;
        return;
    }

    for(long int i = 0; i < count_str; ++i)
    {
        ret_v = -1;
        res = -1;

        res = Decrypt_Input(str[i], labels, label_count, &ret_v, i);

        if(res == -1)
        {
            fprintf(log_file, "error %ld %d\n", i + 1, assm_exit_code);
        }
        
        else if(res / 256 * 256 == ASSM_COMMAND_CODE)
        {
            int half_res = res % 256;
            
            if(half_res == commands[1].code or half_res == commands[2].code)
            {
                fwrite(&half_res, sizeof(int), 1, f);
                fwrite(&ret_v, sizeof(double), 1, f);
            }

            else if(half_res == commands[9].code)
            {
                if(ret_v != -1)
                {
                    // fwrite(&half_res, sizeof(int), 1, f); TODO: починить джампы
                    // fwrite((*labels)[(int) ret_v].pointer, sizeof(long int), 1, f);
                }
            }
            
            else
            {
                fwrite(&half_res, sizeof(int), 1, f);
            }
            
        }
    }

    fclose(f);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int Decrypt_Input(string str, label** labels, long int* label_count, double* ret_v, long int cur_p)
{
    assert(str.start);
    assert(labels);
    assert(*labels);
    assert(label_count);
    assert(ret_v);

    char delim[] = " \n";
    char spec_delim[] = " \n:";

    char* lexem = strtok(str.start, delim);

    string first_part = StrCtor(strlen(lexem), lexem);

    unsigned num = -1;

    if(first_part.start[0] == ':')
    {
        (*label_count)++;

        *labels =(label*) realloc(*labels, sizeof(label) *(*label_count + 1));

        (*labels)[*label_count - 1].label_name = StrCtor(first_part.len - 1, first_part.start + 1);
        (*labels)[*label_count - 1].pointer    = cur_p;

        return ASSM_LABEL_CODE;
    }

    for(unsigned i = 0; i < number_commands; ++i)
    {
        if(!StrCompare(&(commands[i].text), &first_part))
        {
            num = i;
            break;
        }
    }

    switch(num)
    {
        case -1:
        {
            assm_exit_code = ASSM_DECRYPTINPUT_CODE + ASSM_INPUT_EXCEPTION;
            return -1;
            break;
        }

        case 1: //push code
        {
            lexem = strtok(str.start + first_part.len + 1, delim);

            string second_part = StrCtor(strlen(lexem), lexem);

            int counter = 0;

            for(int i = 0; i < second_part.len; ++i)
            {
                if(!isdigit(second_part.start[i]))
                {
                    counter = -1;
                    break;
                }
            }

            if(counter == 0)
            {               
                int res = sscanf(str.start + first_part.len + 1, "%lf", ret_v);

                if(res != 1)
                {
                    assm_exit_code = ASSM_DECRYPTINPUT_CODE + ASSM_PUSH_ARG_ERROR;
                    return -1;
                }

                break;
            }

            else if(second_part.len == 2 and isalpha(second_part.start[0]) and isdigit(second_part.start[1]))
            {
                int *first_half_pointer =(int*) ret_v;
                int *second_half_pointer =(int*) ret_v;
                second_half_pointer += 1;

                *first_half_pointer =(int) toupper(second_part.start[0]);
                *second_half_pointer =(int) second_part.start[1];

                num = 2;
            }

            else
            {
                assm_exit_code = ASSM_DECRYPTINPUT_CODE + ASSM_PUSH_ARG_ERROR;
                return -1;
            }

            StrDtor(second_part);

            break;
        }
        
        case 3: ///pop code
        {


            break;
        }

        case 9: //
        {
            lexem = strtok(str.start + first_part.len + 1, spec_delim);

            string second_part = StrCtor(strlen(lexem), lexem);
            
            for(long int i = 0; i < *label_count; ++i)
            {
                if(!StrCompare(&second_part, &labels[i]->label_name))
                {
                    *ret_v = labels[i]->pointer;
                    break;
                }
            }
            
            StrDtor(second_part);
            break;
        }
    }

    strcat(str.start, first_part.start + first_part.len + 1);

    return ASSM_COMMAND_CODE + commands[num].code;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Assm_PrintExitCode(char* file_name)
{
    FILE* log = NULL;
    int flag = 0;

    if (file_name == NULL)
    {
        log = stdout;
        flag = 1;
    }

    else if (strlen(file_name) == 2 and file_name[0] == '-' and file_name[1] == 'c')
    {
        log = stdout;
        flag = 1;
    }

    else
        log = fopen(file_name, "w");

    int error_code  = assm_exit_code % 100; 
    int func_code   = assm_exit_code / 100 * 100;

    int no_error_status = 0;

    switch(error_code)
    {
        case NO_EXCEPTIONS_ASSM:
            fprintf(log, "No exception found\n");
            no_error_status = 1;
            break;

        case ASSM_INCORRECT_COMMAND:
            fprintf(log, "Incorrect assembler command found in ");
            break;

        case ASSM_INPUT_EXCEPTION:
            fprintf(log, "Incorrect input data found in ");
            break;

        case ASSM_FOPEN_ERROR:
            fprintf(log, "File opening error in ");
            break;

        case ASSM_FCLOSE_ERROR:
            fprintf(log, "File closing error in ");
            break;

        default:
            fprintf(log, "Unkwonw error in ");
            break;
    }

    if(no_error_status)
        return;

    switch(func_code)
    {
        case ASSM_WHICHCOMMAND_CODE:
            fprintf(log, "WhichCommand() ");
            break;

        case ASSM_DECRYPTINPUT_CODE:
            fprintf(log, "DecryptInput() ");
            break;

        case ASSM_ASSEMBLING_CODE:
            fprintf(log, "Assembling() ");
            break;

        default:
            fprintf(log, "unknown ");
            break;
    }

    fprintf(log, "func\n");

    if(!flag)
        fclose(log);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LabelFree(label* labels, long int label_count)
{
    assert(labels);

    for(long int i = 0; i < label_count; ++i)
    {
        StrDtor(labels[i].label_name);
        labels[i].pointer = 0;
    }

    free(labels);
}