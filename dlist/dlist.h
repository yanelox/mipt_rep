#pragma once

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct dl
{
    struct dl* next;
    struct dl* prev;

    int data;
};

typedef struct dl d_list;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

d_list* DListCtor       (int data);

void DListDtor          (d_list* list);

void DListPrint         (d_list* list);

d_list* DListRead       (char* file_name);

d_list* DListReverse    (d_list* list);
