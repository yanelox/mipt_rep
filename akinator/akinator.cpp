#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "special_onegin.cpp"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ak_exit_code = 0;

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

int main (int argc, char* argv[])
{
    if (argc != 3)
    {
        printf ("Incorrect arguments\n");
        return 0;
    }

    TreeEl* tree = StartReading (argv[1]);

    StartGame (tree);

    SaveGraph (*tree, argv[2]);

    StartSaving (*tree, argv[1]);

    TreeDtor (tree);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* TreeCtor (char* content)
{
    assert (content);

    TreeEl* el = (TreeEl*) calloc (1, sizeof (TreeEl));

    int len = strlen (content) + 1;

    el->content = (char*) calloc (len, sizeof (char));

    if (el->content == NULL)
    {
        ak_exit_code = AK_ALLOCATION_ERROR + AK_TREECTOR;
        
        return (TreeEl*) NULL;
    }

    strcpy (el->content, content);

    return el;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AddEl (TreeEl* leave, char* new_object, char* difference)
{
    assert (leave);
    assert (new_object);
    assert (difference);

    int old_object_len = strlen (leave->content) + 1;
    char* old_obgect   = (char*) calloc (old_object_len, sizeof (char));

    int difference_len = strlen (difference);

    strcpy (old_obgect, leave->content); 

    TreeEl* left  = (TreeEl*) calloc (1, sizeof (TreeEl));
    TreeEl* right = (TreeEl*) calloc (1, sizeof (TreeEl));

    if (left == NULL or right == NULL)
    {
        ak_exit_code = AK_ALLOCATION_ERROR + AK_ADDEL;

        return -1;
    }

    left  = TreeCtor (new_object);
    right = TreeCtor (old_obgect);
    
    leave->content = (char*) realloc (leave->content, sizeof (char) * difference_len + sizeof (char));

    if (leave->content == NULL)
    {
        ak_exit_code = AK_ALLOCATION_ERROR + AK_ADDEL;

        return -1;
    }

    strcpy (leave->content, difference);

    leave->left  = left;
    leave->right = right;

    free (old_obgect);

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintTree (TreeEl el, int t_number)
{
    assert (el.content);

    if (el.left != NULL and el.right != NULL)
    {
        for (int i = 0; i < t_number; ++i)
            printf ("\t");

        printf ("(\n");
    
        for (int i = 0; i < t_number; ++i)
            printf ("\t");

        printf ("\"%s\"\n", el.content);

        PrintTree (*el.left,  t_number + 1);
        PrintTree (*el.right, t_number + 1);

        for (int i = 0; i < t_number; ++i)
            printf ("\t");

        printf (")\n");
    }

    else
    {
        for (int i = 0; i < t_number; ++i)
            printf ("\t");

        printf ("(\"%s\")\n", el.content);           
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void SaveNode (TreeEl el, int t_number, FILE* source)
{
    assert (el.content);
    assert (source);

    if (el.left != NULL and el.right != NULL)
    {
        for (int i = 0; i < t_number; ++i)
            fprintf (source, "\t");

        fprintf (source, "(\n");
    
        for (int i = 0; i < t_number; ++i)
            fprintf (source, "\t");

        fprintf (source, "\"%s\"\n", el.content);

        SaveNode (*el.left,  t_number + 1, source);
        SaveNode (*el.right, t_number + 1, source);

        for (int i = 0; i < t_number; ++i)
            fprintf (source, "\t");

        fprintf (source, ")\n");
    }

    else
    {
        for (int i = 0; i < t_number; ++i)
            fprintf (source, "\t");

        fprintf (source, "(\"%s\")\n", el.content);           
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* ReadSave (TreeEl* prev, char* file_copy)
{   
    char delim[]    = "\n\t\"";
    char* lexem     = NULL;

    TreeEl* new_el = NULL;

    lexem = strtok (file_copy, delim);

    if (strlen (lexem) == 1 and lexem[0] == '(')
    {
        lexem = strtok (NULL, delim);

        new_el = TreeCtor (lexem);

        new_el->prev = prev;

        new_el->left  = ReadSave (new_el, NULL);

        if (new_el->left != (TreeEl*) NULL)
        {
            new_el->right = ReadSave (new_el, NULL);

            lexem = strtok (NULL, delim);
        }
        else
            new_el->right = (TreeEl*) NULL;
    }   

    else 
        return (TreeEl*) NULL;

    return new_el;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StartSaving (TreeEl el, char* file_name)
{
    FILE* f = fopen (file_name, "w");

    if (f == NULL)
    {
        printf ("File opening error\n");
        return;
    }

    SaveNode (el, 0, f);

    fclose (f);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* StartReading (char* file_name)
{
    TreeEl* first;

    long int count_sym = CountSymbols (file_name);

    char* savefile_copy = (char*) calloc (count_sym, sizeof (char));

    FromFileToStr (file_name, savefile_copy, count_sym);

    first = ReadSave ((TreeEl*) NULL, savefile_copy);

    return first;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetAns ()
{
    char* answer = (char*) calloc (1000, sizeof (char));

    int input_res = 0;

    input_res = scanf ("%s", answer);

    while (input_res != 1 or strlen (answer) != 1 or (answer[0] != 'y' and answer[0] != 'n'))
    {
        printf ("Incorrect command, please try again\n");

        input_res = scanf ("%s", answer);
    }   

    if (answer[0] == 'y')
        return 1;
    
    else
        return 0;

    free (answer);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StartGame (TreeEl* el)
{
    int input_res = 0;

    printf ("Start game (y/n)?\n");

    input_res = GetAns ();

    if (input_res == 1)
    {
        while (el)
        {
            if (el->left != NULL and el->right != NULL)
            {
                printf ("%s? (y/n)\n", el->content);

                input_res = GetAns ();

                if (input_res == 1)
                    el = el->left;

                else
                    el = el->right;
            }

            else
                break;
        }

        printf ("I think that it is %s\nAm i right? (y/n)\n", el->content);

        input_res = GetAns ();

        if (input_res == 1)
            printf ("EZ\n");
        else
        {
            char* true_ans  = (char*) calloc (1000, sizeof (char));
            char* diff      = (char*) calloc (1000, sizeof (char));

            printf ("Please, input true answer (without spaces)\n");

            scanf ("%s", true_ans);

            printf ("Please, input difference between %s and %s (without spaces)\n", true_ans, el->content);
            printf ("%s...", true_ans);

            scanf ("%s", diff);

            input_res = AddEl (el, true_ans, diff);

            if (input_res == 0)
                printf ("Your object was saved\n");
            else
                printf ("Sorry, error during saving\n");

            free (true_ans);
            free (diff);
        }
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void SaveConnection (TreeEl el, FILE* f)
{
    assert (f);

    if (el.left != NULL and el.right != NULL)
    {
        fprintf (f, "\"%s\" -> \"%s\";\n", el.content, el.left->content);
        fprintf (f, "\"%s\" -> \"%s\";\n", el.content, el.right->content);

        SaveConnection (*el.left,  f);
        SaveConnection (*el.right, f);
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void SaveGraph (TreeEl el, char* file_name)
{
    assert (file_name);

    FILE* f = fopen (file_name, "w");

    if (f == NULL)
    {
        ak_exit_code = AK_ALLOCATION_ERROR + AK_SAVEGRAPH;
        return;
    }

    fprintf (f, "digraph\n{\n");

    SaveConnection (el, f);

    fprintf (f, "}");

    fclose (f);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TreeDtor (TreeEl* el)
{
    assert (el);

    free (el->content);

    if (el->left != NULL and el->right != NULL)
    {
        TreeDtor (el->left);
        TreeDtor (el->right);
    }

    free (el);
}