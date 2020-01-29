// Ian Braudaway
// Implementation file for lexeme class

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "lexeme.h"
#include "types.h"

struct LEXEME
{
    char *type;
    char *string;
    int integer;
    double real;
    LEXEME **aval;
    LEXEME *left;
    LEXEME *right;
    FILE *fp;
};

LEXEME *
newLexeme(char *type, char *token)
{
    LEXEME *lexeme = malloc(sizeof(LEXEME));

    if (lexeme == 0) 
    { 
        fprintf(stderr,"out of memory\n"); 
        exit(1); 
    }

    lexeme->type = type;

    //int, convert string to integer
    if (lexeme->type == INTEGER)
    {
        lexeme->integer = atoi(token);
    }

    //real, convert string to float
    else if (lexeme->type == REAL)
    {
        lexeme->real = atof(token);
    }

    //string or variable, or anything else
    else
    {
        lexeme->string = token;
    }

    return lexeme;
}

LEXEME *
newLexemeInt(int integer)
{
    LEXEME *lexeme = malloc(sizeof(LEXEME));

    if (lexeme == 0) 
    { 
        fprintf(stderr,"out of memory\n"); 
        exit(1); 
    }

    lexeme->type = INTEGER;
    lexeme->integer = integer;

    return lexeme;
}

LEXEME *
newLexemeReal(double real)
{
    LEXEME *lexeme = malloc(sizeof(LEXEME));

    if (lexeme == 0) 
    { 
        fprintf(stderr,"out of memory\n"); 
        exit(1); 
    }

    lexeme->type = REAL;
    lexeme->real = real;

    return lexeme;
}

LEXEME *
newLexemeString(char *string)
{
    LEXEME *lexeme = malloc(sizeof(LEXEME));

    if (lexeme == 0) 
    { 
        fprintf(stderr,"out of memory\n"); 
        exit(1); 
    }

    lexeme->type = STRING;
    lexeme->string = string;

    return lexeme;
}

char *
getType(LEXEME *lex)
{
    if (lex != NULL) 
    {
        return lex->type;
    }

    else
    {
        return NULL;
    }
}

LEXEME *
cons(char *type, LEXEME *left, LEXEME *right)
{
    LEXEME *consLex = newLexeme(type, NULL);
    setLeft(consLex, left);
    setRight(consLex, right);
    return consLex;
}

char *
getStringToken(LEXEME *lex)
{
    if ((lex != NULL) && (lex->string != NULL)) 
    {
        return lex->string;
    }

    else
    {
        return NULL;
    }
}

int
getIntegerToken(LEXEME *lex)
{
    if ((lex != NULL)) 
    {
        return lex->integer;
    }

    else
    {
        return 0;
    }
}

double
getRealToken(LEXEME *lex)
{
    if ((lex != NULL)) 
    {
        return lex->real;
    }

    else
    {
        return 0;
    }
}

LEXEME **
getAvalToken(LEXEME *lex)
{
    if ((lex != NULL)) 
    {
        return lex->aval;
    }

    else
    {
        return NULL;
    }
}

FILE *
getFileToken(LEXEME *lex)
{
    if ((lex != NULL)) 
    {
        return lex->fp;
    }

    else
    {
        return NULL;
    }
}

void
setStringToken(LEXEME *lex, char *setToThis)
{
    lex->string = setToThis;
}

void
setIntegerToken(LEXEME *lex, int setToThis)
{
    lex->integer = setToThis;
}

void
setRealToken(LEXEME *lex, double setToThis)
{
    lex->real = setToThis;
}

void
setAvalToken(LEXEME *lex, int slots)
{
    lex->aval = malloc(sizeof(struct LEXEME *) * slots);
}

void
setFileToken(LEXEME *lex, FILE *file)
{
    lex->fp = file;
}

LEXEME *
getLeft(LEXEME *lex)
{
    if ((lex != NULL) && (lex->left != NULL))
    {
        return lex->left;
    }
    
    else
    {
        return NULL;
    }
}

LEXEME *
getRight(LEXEME *lex)
{
    if ((lex != NULL) && (lex->right != NULL))
    {
        return lex->right;
    }
    
    else
    {
        return NULL;
    }
}

void
setLeft(LEXEME *lex, LEXEME *leftLex)
{
    lex->left = leftLex;
}

void
setRight(LEXEME *lex, LEXEME *rightLex)
{
    lex->right = rightLex;
}

void
display(LEXEME *lex)
{
    fprintf(stdout, "%s ", lex->type);

    //string
    if (lex->type == STRING)
    {
        fprintf(stdout, "\"%s\"\n", lex->string);
    }

    //variable
    else if (lex->type == VARIABLE)
    {
        fprintf(stdout, "%s\n", lex->string);
    }

    //int
    else if (lex->type == INTEGER)
    {
        fprintf(stdout, "%d\n", lex->integer);
    }

    //real
    else if (lex->type == REAL)
    {
        fprintf(stdout, "%f\n", lex->real);
    }

    //no token
    else
    {
        fprintf(stdout, "\n");
    }
}

void
displayLexemeValue(LEXEME *lex)
{
    if (lex != NULL)
    {
        //int
        if (lex->type == INTEGER)
        {
            fprintf(stdout, "%d\n", lex->integer);
        }

        //real
        else if (lex->type == REAL)
        {
            fprintf(stdout, "%f\n", lex->real);
        }

        //string
        else
        {
            fprintf(stdout, "%s\n", lex->string);
        }
    }
    else
    {
        fprintf(stdout, "\n");
    }
}