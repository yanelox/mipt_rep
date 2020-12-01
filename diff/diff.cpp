#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "special_onegin.h"
#include "diff.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int diff_exit_code = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* TreeCtor (int type, int value, el* prev)
{
    assert (type == DIFF_OPERATION_TYPE or type == DIFF_NUMBER_TYPE or DIFF_VARIABLE_TYPE);
    
    TreeEl* new_el = (TreeEl*) calloc (1, sizeof (TreeEl));

    new_el->prev  = prev;

    new_el->type  = type;
    new_el->value = value;

    return new_el;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int isoperation (char sym)
{
    switch (sym)
    {
        case '+':
            return DIFF_SUM;
            break;

        case '-':
            return DIFF_SUB;
            break;

        case '*':
            return DIFF_MUL;
            break;

        case '/':
            return DIFF_DIV;
            break;

        case '^':
            return DIFF_POW;
            break;

        default:
            return 0;
            break;
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char GetOperation (int num)
{
    switch (num)
    {
        case DIFF_SUM:
            return '+';
            break;

        case DIFF_SUB:
            return '-';
            break;

        case DIFF_MUL:
            return '*';
            break;

        case DIFF_DIV:
            return '/';
            break;

        case DIFF_POW:
            return '^';
            break;

        default:
            return '\0';
            break;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* ReadNode (TreeEl* prev, char** source)
{
    assert (source);

    TreeEl* res   = TreeCtor (DIFF_NUMBER_TYPE, 0, prev);

    TreeEl* left  = NULL;
    TreeEl* right = NULL;

    if (res == (TreeEl*) NULL)
    {
        diff_exit_code = DIFF_READNODE + DIFF_ALLOCATION_ERROR;
        
        return (TreeEl*) NULL;
    }

    char sym = (*source)[0];

    int returned_data = 0;

    ReadNode_Save_Error (sym == '(');

    sym = (*source)[1];

    if (sym == '(')
    {
        (*source)++;

        left = ReadNode (res, source);

        ReadNode_Save_Error (left != (TreeEl*) NULL);

        sym = (*source)[0];

        returned_data = isoperation (sym);

        ReadNode_Save_Error (returned_data);

        (*source)++;

        right = ReadNode (res, source);

        ReadNode_Save_Error (right != (TreeEl*) NULL);

        res->type  = DIFF_OPERATION_TYPE;
        res->value = returned_data;

        sym = (*source)[0];

        ReadNode_Save_Error (sym == ')');

        (*source)++;
    }

    else if (isdigit (sym))
    {
        (*source)++;

        char* last_pos = strchr (*source, (int) ')');

        int number = 0;

        ReadNode_Save_Error (last_pos);

        *last_pos = 0;

        returned_data = sscanf (*source, "%d", &number);

        ReadNode_Save_Error (returned_data == 1);

        res->type  = DIFF_NUMBER_TYPE;
        res->value = number;

        *last_pos = ')';

        *source = last_pos + 1;
    }

    else if (isalpha (sym))
    {
        if (sym == 'l' and (*source)[2] == 'n')
        {
            (*source) += 3;

            left = ReadNode (res, source);

            ReadNode_Save_Error ((*source)[0] == ')');

            (*source)++;

            res->type  = DIFF_OPERATION_TYPE;
            res->value = DIFF_LN;
        }        

        else if (sym == 'c' and (*source)[2] == 'o' and (*source)[3] == 's')
        {
            (*source) += 4;

            left = ReadNode (res, source);

            ReadNode_Save_Error ((*source)[0] == ')');

            (*source)++;

            res->type  = DIFF_OPERATION_TYPE;
            res->value = DIFF_COS;
        }

        else if (sym == 's' and (*source)[2] == 'i' and (*source)[3] == 'n')
        {
            (*source) += 4;

            left = ReadNode (res, source);

            ReadNode_Save_Error ((*source)[0] == ')');

            (*source)++;

            res->type  = DIFF_OPERATION_TYPE;
            res->value = DIFF_SIN;
        }

        else
        {
            (*source)++;

            char* last_pos = strchr (*source, (int) ')');

            ReadNode_Save_Error (last_pos);

            --last_pos;

            ReadNode_Save_Error (last_pos == *source);

            res->type  = DIFF_VARIABLE_TYPE;
            res->value = (int) *last_pos; 

            *source = last_pos + 2;
            }
    }

    else
        ReadNode_Save_Error (false);

    res->left  = left;
    res->right = right;

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* StartReading (char* source)
{
    assert (source);

    TreeEl* res = NULL;

    res = ReadNode ((TreeEl*) NULL, &source);

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintTree (TreeEl* tree)
{
    assert (tree);

    printf ("(");

    if (tree->type == DIFF_OPERATION_TYPE)
    {
        if (tree->value == DIFF_LN)
        {
            printf ("ln");
            PrintTree (tree->left);          
        }

        else if (tree->value == DIFF_COS)
        {
            printf ("cos");
            PrintTree (tree->left);
        }

        else if (tree->value == DIFF_SIN)
        {
            printf ("sin");
            PrintTree (tree->left);
        }

        else
        {
            PrintTree (tree->left);
            printf("%c", GetOperation (tree->value));
            PrintTree (tree->right);
        }
    }

    else if (tree->type == DIFF_VARIABLE_TYPE)
        printf ("%c", tree->value);

    else if (tree->type == DIFF_NUMBER_TYPE)
        printf ("%d", tree->value);

    else
        return;

    printf (")");

    if (tree->prev == (TreeEl*) NULL)
        printf ("\n");
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TreeDtor (TreeEl* tree)
{
    assert (tree);

    if (tree->left and tree->right)
    {
        TreeDtor (tree->left);
        TreeDtor (tree->right);
    }

    free (tree);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* CopyNode (TreeEl* source, TreeEl* prev)
{
    assert (source);

    TreeEl* res = TreeCtor (source->type, source->value, prev);

    if (source->left != (TreeEl*) NULL)
        res->left = CopyNode (source->left, res);

    if (source->right != (TreeEl*) NULL)
        res->right = CopyNode (source->right, res);

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* DiffTree (TreeEl* tree, TreeEl* prev)
{
    assert (tree);

    TreeEl* res = TreeCtor (DIFF_NUMBER_TYPE, 0, prev);

    if (tree->type == DIFF_OPERATION_TYPE)
    {   
        res->type = DIFF_OPERATION_TYPE;

        switch (tree->value)
        {
            case DIFF_SUM:
            {
                res->value = DIFF_SUM;

                res->left  = DiffTree (tree->left, res);
                res->right = DiffTree (tree->right, res);

                break;
            }

            case DIFF_MUL:
            {
                res->value = DIFF_SUM;

                TreeEl* left = TreeCtor (DIFF_OPERATION_TYPE, DIFF_MUL, res);
                left->left  = DiffTree (tree->left, res);
                left->right = CopyNode (tree->right, left);
                
                TreeEl* right = TreeCtor (DIFF_OPERATION_TYPE, DIFF_MUL, res);
                right->left  = CopyNode (tree->left, right);
                right->right = DiffTree (tree->right, res);

                res->left  = left;
                res->right = right; 

                break;
            }

            case DIFF_SUB:
            {
                res->value = DIFF_SUB;

                res->left  = DiffTree (tree->left, res);
                res->right = DiffTree (tree->right, res);

                break;
            }

            case DIFF_DIV:
            {
                res->value = DIFF_DIV;

                TreeEl* numerator  = TreeCtor (DIFF_OPERATION_TYPE, DIFF_SUB, res);

                TreeEl* first  = TreeCtor (DIFF_OPERATION_TYPE, DIFF_MUL, numerator);
                first->left    = DiffTree (tree->left, res);
                first->right   = CopyNode (tree->right, first);

                TreeEl* second = TreeCtor (DIFF_OPERATION_TYPE, DIFF_MUL, numerator);
                second->left   = CopyNode (tree->left, second);
                second->right  = DiffTree (tree->right, res);

                numerator->left  = first;
                numerator->right = second;

                TreeEl* denominator = TreeCtor (DIFF_OPERATION_TYPE, DIFF_MUL, res);
                denominator->left  = CopyNode (tree->right, denominator);
                denominator->right = CopyNode (tree->right, denominator);

                res->left  = numerator;
                res->right = denominator;

                break; 
            }

            case DIFF_POW:
            {
                res->value = DIFF_MUL;

                TreeEl* left  = CopyNode (tree, res);

                TreeEl* right = TreeCtor (DIFF_OPERATION_TYPE, DIFF_SUM, res);

                TreeEl* first = TreeCtor (DIFF_OPERATION_TYPE, DIFF_MUL, right);
                first->left   = DiffTree (tree->right, first);
                first->right  = TreeCtor (DIFF_OPERATION_TYPE, DIFF_LN, first);

                first->right->left = CopyNode (tree->left, first->right);

                TreeEl* second = TreeCtor (DIFF_OPERATION_TYPE, DIFF_MUL, right);

                second->left   = TreeCtor (DIFF_OPERATION_TYPE, DIFF_DIV, second);
                second->left->left  = CopyNode (tree->right, second->left);
                second->left->right = CopyNode (tree->left,  second->left); 

                second->right = DiffTree (tree->left, second);

                right->left  = first;
                right->right = second;

                res->left  = left;
                res->right = right;

                break;
            }

            case DIFF_LN:
            {
                res->value = DIFF_DIV;

                res->left  = DiffTree (tree->left, res);
                res->right = CopyNode (tree->left, res);

                break;
            }

            case DIFF_COS:
            {
                res->value = DIFF_MUL;

                TreeEl* left = TreeCtor (DIFF_OPERATION_TYPE, DIFF_SUB, res);
                left->left   = TreeCtor (DIFF_NUMBER_TYPE, 0, left);
                left->right  = TreeCtor (DIFF_OPERATION_TYPE, DIFF_SIN, left);

                left->right->left = CopyNode (tree->left, left->right);

                res->left  = left;
                res->right = DiffTree (tree->left, res);

                break;
            }

            case DIFF_SIN:
            {
                res->value = DIFF_MUL;

                res->left = TreeCtor (DIFF_OPERATION_TYPE, DIFF_COS, res);
                res->left->left = CopyNode (tree->left, res->left);

                res->right = DiffTree (tree->left, res);

                break;
            }

            default:
                break;
        }
    }

    else if (tree->type == DIFF_NUMBER_TYPE)
    {
        ; //Look for initial value of res
    }

    else if (tree->type == DIFF_VARIABLE_TYPE)
    {
        res->value = 1; // Look for initial value of res
    }

    else
        return (TreeEl*) NULL;

    return res;
}