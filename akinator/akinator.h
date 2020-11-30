#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

extern int ak_exit_code;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief Enumerate of error's codes
*/

enum ak_exit_codes
{
    AK_NO_EXCEPTIONS    = 0x00,
    AK_ALLOCATION_ERROR = 0x22,
    AK_FREE_ERROR       = 0x24,
    AK_FILEOPEN_ERROR   = 0x27,
    AK_ONEGIN_ERROR     = 0x29
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief Enumerate of function's codes
*/

enum ak_func_code
{
    AK_TREECTOR     = 0x2200,
    AK_ADDEL        = 0x2400,
    AK_SAVETREE     = 0x2700,
    AK_READSAVE     = 0x2900,
    AK_SAVEGRAPH    = 0x4200
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief Initialization of tree-element type
*/

struct element
{
    char* content;

    element* prev;
    element* left;
    element* right;

};

typedef struct element TreeEl;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which initialize variable with 'TreeEl' type (allocate memory for
            it and write content in

    @param [in] content Pointer to start of string which content text which you want 
                to put in tree-element

    @return     Pointer to 'TreeEl' type object
*/

TreeEl* TreeCtor            (char* content);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief Function which add a new element to tree

    @param [in] leave Pointer to tree-element (leave) which we want to rewrite as
                knot (with saving this leave as a son of new knot)

    @param [in] new_object Content of new son of new knot
    
    @param [in] difference Content of new knot

    @return     Result of work of this function. 0 if all correct, -1, if smth
                incorrect (you should check 'ak_exit_code' global variable)
*/

int AddEl                   (TreeEl* leave, char* new_object, char* difference);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Recursive function which print info about one node to console 
            and call itslef for it's two sons

    @param [in] el Element of tree
    
    @param [in] t_number Number of tabulation which function have to print
*/

void PrintTree              (TreeEl el, int t_number);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which start saving infromation about tree to file
    
    @param [in] el First tree element

    @param [in] file_name Name of file where you want to save info about tree
*/

void StartSaving            (TreeEl el, char* file_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Recursive function which save info about node to file and than call 
            itself for it's two sons

    @param [in] el Element which you want to save to file

    @param [in] t_number Number of tabulation which function have to print

    @param [in] source Stream which connected with file where tou want to save node
*/

void SaveNode               (TreeEl el, int t_number, FILE* source);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


/*!
    \brief  Function which start reading info about tree from file

    @param [in] file_name Name of file where we want to read tree

    @return Pointer to generated tree
*/

TreeEl* StartReading        (char* file_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


/*!
    \brief  Recursive function which read one node from string

    @param [in] prev Pointer to previous node (to "father" node)

    @param [in] file_copy String where we read info about node

    @return Pointer to new node
*/

TreeEl* ReadSave            (TreeEl* prev, char* file_copy);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function was created for reading users answers from console and check them
            (user have to answer only y/n (yes or no)), all other answers is incorrect 
            and if user get incorrect answer he well be asked again for a correct 
            answer

    @return 0, if answer was 'n' (no) and 1, if answer was 'y' (yes)
*/

int GetAns                  ();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which start "Akinator-game"

    @param [in] el First tree element which well be used during the game
*/

void StartGame              (TreeEl* el);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Recursive function is used for saving info about connection between 
            "father" node with it's "sons" to file in necessary form for using this 
            file in "dot" utility and than this function call itself for it's "sons"

    @param [in] el Pointer to node which connections you want to save

    @param [in] f Stream which connected with file where you want to save node
*/

void SaveConnection         (TreeEl* el, FILE* f);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Function which start saving all connections between nodes in tree in 
            correct form in file for using this file in "dot" utility.

    @param [in] el First tree element

    @param [in] file_name Name of file where you want to save your graph
*/

void SaveGraph              (TreeEl el, char* file_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
    \brief  Recursive function which destruct all tree elements and clean memory from 
            them (it is used after end of game and end of saving tree and tree graph)

    @param [in] el Firt tree element
*/

void TreeDtor               (TreeEl* el);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx