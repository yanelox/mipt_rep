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

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

TreeEl* TreeSimplification (TreeEl* tree, TreeEl* prev)
{
    assert (tree);

    TreeEl* new_tree = tree;

    if (tree->left != (TreeEl*) NULL)
        tree->left = TreeSimplification (tree->left, tree);

    if (tree->right != (TreeEl*) NULL)
        tree->right = TreeSimplification (tree->right, tree);

    if (tree->type == DIFF_OPERATION_TYPE)
    {
        switch (tree->value)
        {
            case DIFF_MUL:
            {
                if ((tree->left->type  == DIFF_NUMBER_TYPE and tree->left->value  == 0) or
                    (tree->right->type == DIFF_NUMBER_TYPE and tree->right->value == 0))
                {
                    new_tree = TreeCtor (DIFF_NUMBER_TYPE, 0, prev);

                    TreeDtor (tree);
                }

                else if (tree->left->type == DIFF_NUMBER_TYPE and tree->left->value == 1)
                {
                    new_tree = CopyNode (tree->right, prev);

                    TreeDtor (tree);
                }

                else if (tree->right->type == DIFF_NUMBER_TYPE and tree->right->value == 1)
                {
                    new_tree = CopyNode (tree->left, prev);

                    TreeDtor (tree);
                }

                break;
            }

            case DIFF_DIV:
            {
                if (tree->right->type == DIFF_NUMBER_TYPE and tree->right->value == 1)
                {
                    new_tree = CopyNode (tree->left, prev);

                    TreeDtor (tree);
                }

                break;
            }

            case DIFF_POW:
            {
                if (tree->right->type == DIFF_NUMBER_TYPE and tree->right->value == 1)
                {
                    new_tree = CopyNode (tree->left, prev);

                    TreeDtor (tree);
                }

                else if (tree->right->type == DIFF_NUMBER_TYPE and tree->right->value == 0)
                {
                    new_tree = TreeCtor (DIFF_NUMBER_TYPE, 1, prev);

                    TreeDtor (tree);
                }

                break;
            }

            case DIFF_SUM:
            {
                if (tree->left->type == DIFF_NUMBER_TYPE and 
                    tree->right->type == DIFF_NUMBER_TYPE)
                {
                    new_tree = TreeCtor (DIFF_NUMBER_TYPE, tree->left->value + tree->right->value, prev);

                    TreeDtor (tree);
                }

                else if (tree->left->type == DIFF_NUMBER_TYPE and
                         tree->left->value == 0)
                {
                    new_tree = CopyNode (tree->right, prev);

                    TreeDtor (tree);
                }

                else if (tree->right->type == DIFF_NUMBER_TYPE and
                         tree->right->value == 0)
                {
                    new_tree == CopyNode (tree->left, prev);

                    TreeDtor (tree);
                }

                break;
            }

            default:
                break;
        }
    }

    return new_tree;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void SaveNodeL (TreeEl* tree, FILE* doc)
{
    assert (tree);
    assert (doc);
    
    switch (tree->type)
    {
        case DIFF_OPERATION_TYPE:
        {
            switch (tree->value)
            {
                case DIFF_SUM:
                {
                    SaveNodeL (tree->left, doc);
                    
                    fprintf (doc, " + ");
                    
                    SaveNodeL (tree->right, doc);

                    break;
                }

                case DIFF_MUL:
                {
                    if (tree->left->type == DIFF_OPERATION_TYPE and
                        (tree->left->value == DIFF_SUM or tree->left->value == DIFF_SUB))
                    {
                        fprintf (doc, "\\left( ");
                        
                        SaveNodeL (tree->left, doc);

                        fprintf (doc, "\\right) ");
                    }

                    else
                        SaveNodeL (tree->left, doc);

                    fprintf (doc, "\\cdot ");

                    if (tree->right->type == DIFF_OPERATION_TYPE and
                        (tree->right->value == DIFF_SUM or tree->right->value == DIFF_SUB))
                    {
                        fprintf (doc, "\\left( ");

                        SaveNodeL (tree->right, doc);

                        fprintf (doc, "\\right) ");
                    }

                    else
                        SaveNodeL (tree->right, doc);

                    break;   
                }

                case DIFF_DIV:
                {
                    fprintf (doc, "\\dfrac{");

                    SaveNodeL (tree->left, doc);

                    fprintf (doc, "}{");

                    SaveNodeL (tree->right, doc);

                    fprintf (doc, "} ");

                    break;
                }

                case DIFF_SUB:
                {
                    SaveNodeL (tree->left, doc);

                    fprintf (doc, " - ");
                    
                    SaveNodeL (tree->right, doc);

                    break;
                }

                case DIFF_POW:
                {
                    if (tree->left->type == DIFF_OPERATION_TYPE)
                    {
                        fprintf (doc, "\\left( ");
                        SaveNodeL (tree->left, doc);
                        fprintf (doc, "\\right) ");
                    }

                    else
                        SaveNodeL (tree->left, doc);

                    fprintf (doc, "^{");

                    SaveNodeL (tree->right, doc);

                    fprintf (doc, "}");

                    break;
                }

                case DIFF_LN:
                {
                    fprintf (doc, "\\ln (");
                    
                    SaveNodeL (tree->left, doc);

                    fprintf (doc, ") ");

                    break;
                }

                case DIFF_COS:
                {
                    fprintf (doc, "\\cos (");
                    
                    SaveNodeL (tree->left, doc);

                    fprintf (doc, ") ");   

                    break;             
                }

                case DIFF_SIN:
                {
                    fprintf (doc, "\\sin (");
                    
                    SaveNodeL (tree->left, doc);

                    fprintf (doc, ")");

                    break;
                }

                default:
                    break;
            }

            break;
        }

        case DIFF_NUMBER_TYPE:
        {
            fprintf (doc, "%d", tree->value);

            break;
        }

        case DIFF_VARIABLE_TYPE:
        {
            fprintf (doc, "%c", tree->value);

            break;
        }

        default:
            break;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StartLSaving (TreeEl* tree, FILE* doc)
{
    assert (tree);
    assert (doc);

    fprintf (doc, "$");

    SaveNodeL (tree, doc);

    fprintf (doc, "$");
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void MakeLFile (TreeEl* tree, TreeEl* diff_tree, char* file_name)
{
    assert (tree);
    assert (diff_tree);
    assert (file_name);

    FILE* f = fopen (file_name, "w");
 
    fprintf (f, "\\documentclass[12pt,a4paper,fleqn]{article}\n");
    fprintf (f, "\\usepackage[utf8]{inputenc}\n");
    fprintf (f, "\\usepackage{amssymb, amsmath, multicol}\n");
    fprintf (f, "\\usepackage[russian]{babel}\n");
    fprintf (f, "\\usepackage{graphicx}\n");
    fprintf (f, "\\graphicspath{{pictures/}}\n");
    fprintf (f, "\\DeclareGraphicsExtensions{.pdf,.png,.jpg}\n");
    fprintf (f, "\\usepackage[shortcuts,cyremdash]{extdash}\n");
    fprintf (f, "\\usepackage{wrapfig}\n");
    fprintf (f, "\\usepackage{floatflt}\n");
    fprintf (f, "\\usepackage{lipsum}\n");
    fprintf (f,"\\usepackage{concmath}\n");    
    fprintf (f, "\\usepackage{euler}\n");
    fprintf (f, "\\usepackage{tikz}\n");
    fprintf (f, "\\usetikzlibrary{graphs}\n\n");
    fprintf (f, "\\oddsidemargin=-15.4mm\n");
    fprintf (f, "\\textwidth=190mm\n");
    fprintf (f, "\\headheight=-32.4mm\n");
    fprintf (f, "\\textheight=277mm\n");
    fprintf (f, "\\tolerance=100\n");
    fprintf (f, "\\parindent=0pt\n");
    fprintf (f, "\\parskip=8pt\n");
    fprintf (f, "\\pagestyle{empty}\n");
    fprintf (f, "\\renewcommand{\\tg}{\\mathop{\\mathrm{tg}}\\nolimits}\n");
    fprintf (f, "\\renewcommand{\\ctg}{\\mathop{\\mathrm{ctg}}\\nolimits}\n");
    fprintf (f, "\\renewcommand{\\arctan}{\\mathop{\\mathrm{arctg}}\\nolimits}\n");
    fprintf (f, "\\newcommand{\\divisible}{\\mathop{\\raisebox{-2pt}{\\vdots}}}\n\n\n");
    fprintf (f, "\\begin{document}\n");

    StartLSaving (tree, f);

    fprintf (f, "\\newline\n");

    StartLSaving (diff_tree, f);

    fprintf (f, "\n\\end{document}");

    fclose (f);
}