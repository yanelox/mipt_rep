#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "special_onegin.cpp"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ak_exit_code = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum ak_exit_codes
{
    AK_NO_EXCEPTIONS    = 0x00,
    AK_ALLOCATION_ERROR = 0x22,
    AK_FREE_ERROR       = 0x24,
    AK_FILEOPEN_ERROR   = 0x27,
    AK_ONEGIN_ERROR     = 0x29
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum ak_func_code
{
    AK_TREECTOR     = 0x2200,
    AK_ADDEL        = 0x2400,
    AK_SAVETREE     = 0x2700,
    AK_READSAVE     = 0x2900,
    AK_SAVEGRAPH    = 0x4200
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct element
{
    char* content;

    element* prev;
    element* left;
    element* right;

};

typedef struct element TreeEl;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* TreeCtor            (char* content);

int AddEl                   (TreeEl* leave, char* new_object, char* difference);

void PrintTree              (TreeEl el, int t_number);

void StartSaving            (TreeEl el, char* file_name);

void SaveTree               (TreeEl el, int t_number, FILE* source);

TreeEl* StartReading        (char* file_name);

TreeEl* ReadSave            (TreeEl* prev, char* file_copy);

int GetAns                  ();

void StartGame              (TreeEl* el);

void SaveConnection         (TreeEl* el, FILE* f);

void SaveGraph              (TreeEl el, char* file_name);

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
    
    leave->content = (char*) realloc (leave->content, sizeof (char) * difference_len);

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

void SaveTree (TreeEl el, int t_number, FILE* source)
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

        SaveTree (*el.left,  t_number + 1, source);
        SaveTree (*el.right, t_number + 1, source);

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

    SaveTree (el, 0, f);

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