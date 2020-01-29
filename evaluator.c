// Ian Braudaway
// Implementation file for evaluator

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "lexer.h"
#include "lexeme.h"
#include "types.h"
#include "recognizer.h"
#include "environment.h"
#include "evaluator.h"

extern int countCL;
extern char **argsCL;

static LEXEME *evalUNot(LEXEME *, LEXEME *);
static LEXEME *evalUMinus(LEXEME *, LEXEME *);
static LEXEME *evalPlus(LEXEME *, LEXEME *);
static LEXEME *evalMinus(LEXEME *, LEXEME *);
static LEXEME *evalMultiply(LEXEME *, LEXEME *);
static LEXEME *evalDivide(LEXEME *, LEXEME *);
static LEXEME *evalNot(LEXEME *, LEXEME *);
static LEXEME *evalCe(LEXEME *, LEXEME *);
static LEXEME *evalLt(LEXEME *, LEXEME *);
static LEXEME *evalLte(LEXEME *, LEXEME *);
static LEXEME *evalGt(LEXEME *, LEXEME *);
static LEXEME *evalGte(LEXEME *, LEXEME *);
static LEXEME *evalMod(LEXEME *, LEXEME *);
static LEXEME *evalAnd(LEXEME *, LEXEME *);
static LEXEME *evalOr(LEXEME *, LEXEME *);
static LEXEME *evalAssign(LEXEME *, LEXEME *);
static LEXEME *evalDot(LEXEME *, LEXEME*);
static LEXEME *evalBlock(LEXEME *, LEXEME *);
static LEXEME *evalVarDef(LEXEME *, LEXEME *);
static LEXEME *evalFuncDef(LEXEME *, LEXEME *);
static LEXEME *evalLambda(LEXEME *, LEXEME *);
static LEXEME *getClosureParams(LEXEME *);
static LEXEME *getClosureBody(LEXEME *);
static LEXEME *getClosureEnvironment(LEXEME *);
static LEXEME *evalAt(LEXEME *, LEXEME *);
static LEXEME *evalGetArgCount();
static LEXEME *evalGetArg(LEXEME *);
static LEXEME *evalPrint(LEXEME *);
static LEXEME *evalFuncCall(LEXEME *, LEXEME *);
static LEXEME *evalArgs(LEXEME *, LEXEME *);
static LEXEME *evalStatements(LEXEME *, LEXEME *);
static LEXEME *evalWhile(LEXEME *, LEXEME *);
static LEXEME *evalIf(LEXEME *, LEXEME *);
static LEXEME *evalElse(LEXEME *, LEXEME *);
static LEXEME *evalReturn(LEXEME *, LEXEME *);
static LEXEME *evalMoreProgram(LEXEME *, LEXEME *);
static LEXEME *evalEnd(LEXEME *, LEXEME *);
static LEXEME *evalNewArray(LEXEME *);
static LEXEME *evalGetArray(LEXEME *);
static LEXEME *evalSetArray(LEXEME *);
static LEXEME *evalOpenFileForReading(LEXEME *);
static LEXEME *evalReadInteger(LEXEME *);
static LEXEME *evalAtFileEnd(LEXEME *);
static LEXEME *evalCloseFile(LEXEME *);

LEXEME *
eval(LEXEME *tree, LEXEME *env)
{
    if (getType(tree) == INTEGER)
    {
        return tree;
    }
    else if (getType(tree) == REAL)
    { 
        return tree;
    }
    else if (getType(tree) == VARIABLE)
    { 
        return lookup(tree, env);
    }
    else if (getType(tree) == VARIABLE_EXPR)
    {
        return evalFuncCall(tree, env);
    }
    else if (getType(tree) == STRING)
    { 
        return tree;
    }
    else if (getType(tree) == OPEN_BRACKET)
    {
        return eval(getRight(tree), env);
    }
    else if (getType(tree) == OPEN_BLOCK)
    {
        return evalBlock(tree, env);
    }
    else if (getType(tree) == UMINUS)
    {
        return evalUMinus(tree, env);
    }
    else if (getType(tree) == UNOT)
    {
        return evalUNot(tree, env);
    }
    else if (getType(tree) == NOT)
    {
        return evalNot(tree, env);
    }
    else if (getType(tree) == PLUS)
    {
        return evalPlus(tree, env);
    }
    else if (getType(tree) == MINUS)
    {
        return evalMinus(tree, env);
    }
    else if (getType(tree) == MULTIPLY)
    {
        return evalMultiply(tree, env);
    }
    else if (getType(tree) == DIVIDE)
    {
        return evalDivide(tree, env);
    }
    else if (getType(tree) == LESS_THAN)
    {
        return evalLt(tree, env);
    }
    else if (getType(tree) == LESS_THAN_EQUAL)
    {
        return evalLte(tree, env);
    }
    else if (getType(tree) == GREATER_THAN)
    {
        return evalGt(tree, env);
    }
    else if (getType(tree) == GREATER_THAN_EQUAL)
    {
        return evalGte(tree, env);
    }
    else if (getType(tree) == EQUAL)
    {
        return evalAssign(tree, env);
    }
    else if (getType(tree) == DOT)
    {
        return evalDot(tree, env);
    }
    else if (getType(tree) == COMPARE_EQUAL)
    {
        return evalCe(tree, env);
    }
    else if (getType(tree) == MODULO)
    {
        return evalMod(tree, env);
    }
    else if (getType(tree) == OR)
    {
        return evalOr(tree, env);
    }
    else if (getType(tree) == AND)
    {
        return evalAnd(tree, env);
    }
    else if (getType(tree) == AT)
    {
        return evalAt(getRight(tree), env);
    }
    else if (getType(tree) == IF)
    {
        return evalIf(tree, env);
    }
    else if (getType(tree) == ELSE)
    {
        return evalElse(tree, env);
    }
    else if (getType(tree) == WHILE)
    {
        return evalWhile(tree, env);
    }
    else if (getType(tree) == RETURN)
    {
        return evalReturn(tree, env);
    }
    else if (getType(tree) == MOREPROGRAM)
    {
        return evalMoreProgram(tree, env);
    }
    else if (getType(tree) == VAR)
    {
        return evalVarDef(tree, env);
    }
    else if (getType(tree) == FUNC)
    {
        return evalFuncDef(tree, env);
    }
    else if (getType(tree) == LAMBDA)
    {
        return evalLambda(tree, env);
    }
    else if (getType(tree) == ARGLIST)
    {
        return evalArgs(tree, env);
    }
    else if (getType(tree) == STATEMENTS)
    {
        return evalStatements(tree, env);
    }
    else if (getType(tree) == ENDofINPUT)
    {
        return evalEnd(tree, env);
    }
    else if (getType(tree) == GLUE)
    {
        return tree;
    }
    else if (getType(tree) == NULL)
    {
        return tree;
    }
    else 
    {
        printf("EVALUATOR: bad EVAL type: %s\n", getType(tree)); 
        return tree;
    }  
}

LEXEME *
evalUNot(LEXEME *tree, LEXEME *env)
{
    LEXEME *right = eval(getRight(tree), env);

    if (getType(right) == INTEGER)
    {
        if (getIntegerToken(right) == 0)
        {
            return newLexeme(INTEGER, "1");
        }
        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else
    {
        printf("EVALUATOR: incompatible UNOT operation.\n");
        exit(1);
    }
}

char *
strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

LEXEME *
evalUMinus(LEXEME *tree, LEXEME *env)
{
    LEXEME *right = eval(getRight(tree), env);
    LEXEME *returnLex;

    if (getType(right) == INTEGER)
    {
        returnLex = newLexemeInt(- getIntegerToken(right));
        return returnLex;
    }
    else if (getType(right) == REAL)
    {
        returnLex = newLexemeReal(- getRealToken(right));
        return returnLex;
    }
    else if (getType(right) == STRING)
    {
        returnLex = newLexeme(STRING, NULL);
        setStringToken(returnLex, strrev(getStringToken(right)));
        return returnLex;
    }
    else
    {
        printf("EVALUATOR: incompatible UMINUS operation.\n");
        exit(1);
    }
}

/**
 * Ansi C "itoa" based on Kernighan & Ritchie's "Ansi C":
 */
    
void 
strreverse(char* begin, char* end) 
{
    char aux;
    
    while(end>begin)
        aux=*end, *end--=*begin, *begin++=aux;
}
    
void 
itoa(int value, char* str, int base) 
{
    
    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    
    char* wstr=str;
    
    int sign;
    
    // Validate base
    
    if (base<2 || base>35){ *wstr='\0'; return; }
    
    // Take care of sign
    
    if ((sign=value) < 0) value = -value;
    
    // Conversion. Number is reversed.
    
    do *wstr++ = num[value%base]; while(value/=base);
    
    if(sign<0) *wstr++='-';
    
    *wstr='\0';
    
    // Reverse string

    strreverse(str,wstr-1);
}

LEXEME *
evalPlus(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);
    char buffer[20];
    LEXEME *returnLex;

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        returnLex = newLexemeInt(getIntegerToken(left) + getIntegerToken(right));
        return returnLex;
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        returnLex = newLexemeReal(getIntegerToken(left) + getRealToken(right));
        return returnLex;
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        returnLex = newLexemeReal(getRealToken(left) + getIntegerToken(right));
        return returnLex;
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        returnLex = newLexemeReal(getRealToken(left) + getRealToken(right));
        return returnLex;
    }
    else if ((getType(left) == INTEGER) && (getType(right) == STRING))
    {
        returnLex = newLexeme(STRING, NULL);
        itoa(getIntegerToken(left), buffer, 10);
        setStringToken(returnLex, strcat(buffer, getStringToken(right)));
        return returnLex;
    }
    else if ((getType(left) == STRING) && (getType(right) == INTEGER))
    {
        returnLex = newLexeme(STRING, NULL);
        itoa(getIntegerToken(right), buffer, 10);
        setStringToken(returnLex, strcat(getStringToken(left), buffer));
        return returnLex;
    }
    else if ((getType(left) == REAL) && (getType(right) == STRING))
    {
        returnLex = newLexeme(STRING, NULL);
        itoa(getRealToken(left), buffer, 10);
        setStringToken(returnLex, strcat(buffer, getStringToken(right)));
        return returnLex;
    }
    else if ((getType(left) == STRING) && (getType(right) == REAL))
    {
        returnLex = newLexeme(STRING, NULL);
        itoa(getRealToken(right), buffer, 10);
        setStringToken(returnLex, strcat(getStringToken(left), buffer));
        return returnLex;
    }
    else if ((getType(left) == STRING) && (getType(right) == STRING))
    {
        returnLex = newLexeme(STRING, NULL);
        setStringToken(returnLex, strcat(getStringToken(left), getStringToken(right)));
        return returnLex;
    }
    else
    {
        printf("EVALUATOR: incompatible PLUS operation.\n");
        exit(1);
    }

}

LEXEME *
evalMinus(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);
    LEXEME *returnLex;

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        returnLex = newLexemeInt(getIntegerToken(left) - getIntegerToken(right));
        return returnLex;
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        returnLex = newLexemeReal(getIntegerToken(left) - getRealToken(right));
        return returnLex;
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        returnLex = newLexemeReal(getRealToken(left) - getIntegerToken(right));
        return returnLex;
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        returnLex = newLexemeReal(getRealToken(left) - getRealToken(right));
        return returnLex;
    }
    else
    {
        printf("EVALUATOR: incompatible MINUS operation.\n");
        exit(1);
    }
}

LEXEME *
evalMultiply(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);
    LEXEME *returnLex;

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        returnLex = newLexemeInt(getIntegerToken(left) * getIntegerToken(right));
        return returnLex;
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        returnLex = newLexemeReal(getIntegerToken(left) * getRealToken(right));
        return returnLex;
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        returnLex = newLexemeReal(getRealToken(left) * getIntegerToken(right));
        return returnLex;
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        returnLex = newLexemeReal(getRealToken(left) * getRealToken(right));
        return returnLex;
    }
    else
    {
        printf("EVALUATOR: incompatible MULTIPLY operation.\n");
        exit(1);
    }
}

LEXEME *
evalDivide(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);
    LEXEME *returnLex;

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        returnLex = newLexemeInt(getIntegerToken(left) / getIntegerToken(right));
        return returnLex;
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        returnLex = newLexemeReal(getIntegerToken(left) / getRealToken(right));
        return returnLex;
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        returnLex = newLexemeReal(getRealToken(left) / getIntegerToken(right));
        return returnLex;
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        returnLex = newLexemeReal(getRealToken(left) / getRealToken(right));
        return returnLex;
    }
    else
    {
        printf("EVALUATOR: incompatible DIVIDE operation.\n");
        exit(1);
    }
}

LEXEME *
evalNot(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        if (getIntegerToken(left) != getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        if (getIntegerToken(left) != getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        if (getRealToken(left) != getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        if (getRealToken(left) != getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == INTEGER) && (getType(right) == STRING))
    {
        return newLexeme(INTEGER, "1");
    }
    else if ((getType(left) == STRING) && (getType(right) == INTEGER))
    {
        return newLexeme(INTEGER, "1");
    }
    else if ((getType(left) == REAL) && (getType(right) == STRING))
    {
        return newLexeme(INTEGER, "1");
    }
    else if ((getType(left) == STRING) && (getType(right) == REAL))
    {
        return newLexeme(INTEGER, "1");
    }
    else if ((getType(left) == STRING) && (getType(right) == STRING))
    {
        if (strcmp(getStringToken(left), getStringToken(right)) != 0)
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else
    {
        printf("EVALUATOR: incompatible NOT operation.\n");
        exit(1);
    }   
}

LEXEME *
evalCe(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        if (getIntegerToken(left) == getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        if (getIntegerToken(left) == getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        if (getRealToken(left) == getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        if (getRealToken(left) == getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == INTEGER) && (getType(right) == STRING))
    {
        return newLexeme(INTEGER, "0");
    }
    else if ((getType(left) == STRING) && (getType(right) == INTEGER))
    {
        return newLexeme(INTEGER, "0");
    }
    else if ((getType(left) == REAL) && (getType(right) == STRING))
    {
        return newLexeme(INTEGER, "0");
    }
    else if ((getType(left) == STRING) && (getType(right) == REAL))
    {
        return newLexeme(INTEGER, "0");
    }
    else if ((getType(left) == STRING) && (getType(right) == STRING))
    {
        if (strcmp(getStringToken(left), getStringToken(right)) == 0)
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else
    {
        printf("EVALUATOR: incompatible COMPARE_EQUAL operation.\n");
        exit(1);
    }   
}

LEXEME *
evalLt(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        if (getIntegerToken(left) < getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        if (getIntegerToken(left) < getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        if (getRealToken(left) < getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        if (getRealToken(left) < getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else
    {
        printf("EVALUATOR: incompatible LESS_THAN operation.\n");
        exit(1);
    }   
}

LEXEME *
evalLte(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        if (getIntegerToken(left) <= getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        if (getIntegerToken(left) <= getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        if (getRealToken(left) <= getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        if (getRealToken(left) <= getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else
    {
        printf("EVALUATOR: incompatible LESS_THAN_EQUAL operation.\n");
        exit(1);
    }   
}

LEXEME *
evalGt(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        if (getIntegerToken(left) > getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        if (getIntegerToken(left) > getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        if (getRealToken(left) > getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        if (getRealToken(left) > getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else
    {
        printf("EVALUATOR: incompatible GREATER_THAN operation.\n");
        exit(1);
    }   
}

LEXEME *
evalGte(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        if (getIntegerToken(left) >= getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        if (getIntegerToken(left) >= getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        if (getRealToken(left) >= getIntegerToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        if (getRealToken(left) >= getRealToken(right))
        {
            return newLexeme(INTEGER, "1");
        }

        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else
    {
        printf("EVALUATOR: incompatible GREATER_THAN_EQUAL operation.\n");
        exit(1);
    }   
}

LEXEME *
evalMod(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);
    LEXEME *returnLex;

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        returnLex = newLexemeInt(getIntegerToken(left) % getIntegerToken(right));
        return returnLex;
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        returnLex = newLexemeInt(fmod(getIntegerToken(left), getRealToken(right)));
        return returnLex;
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        returnLex = newLexemeInt(fmod(getRealToken(left), getIntegerToken(right)));
        return returnLex;
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        returnLex = newLexemeInt(fmod(getRealToken(left), getRealToken(right)));
        return returnLex;
    }
    else
    {
        printf("EVALUATOR: incompatible MODULO operation.\n");
        exit(1);
    }   
}

LEXEME *
evalAnd(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        if ((getIntegerToken(left) != 0) && (getIntegerToken(right) != 0))
        {
            return newLexeme(INTEGER, "1");
        }
        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        if ((getIntegerToken(left) != 0) && (getRealToken(right) != 0))
        {
            return newLexeme(INTEGER, "1");
        }
        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        if ((getRealToken(left) != 0) && (getIntegerToken(right) != 0))
        {
            return newLexeme(INTEGER, "1");
        }
        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        if ((getRealToken(left) != 0) && (getRealToken(right) != 0))
        {
            return newLexeme(INTEGER, "1");
        }
        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else
    {
        printf("EVALUATOR: incompatible AND operation.\n");
        exit(1);
    }   
}

LEXEME *
evalOr(LEXEME *tree, LEXEME *env)
{
    LEXEME *left = eval(getLeft(tree), env);
    LEXEME *right = eval(getRight(tree), env);

    if ((getType(left) == INTEGER) && (getType(right) == INTEGER))
    {
        if ((getIntegerToken(left) != 0) || (getIntegerToken(right) != 0))
        {
            return newLexeme(INTEGER, "1");
        }
        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == INTEGER) && (getType(right) == REAL))
    {
        if ((getIntegerToken(left) != 0) || (getRealToken(right) != 0))
        {
            return newLexeme(INTEGER, "1");
        }
        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == INTEGER))
    {
        if ((getRealToken(left) != 0) || (getIntegerToken(right) != 0))
        {
            return newLexeme(INTEGER, "1");
        }
        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else if ((getType(left) == REAL) && (getType(right) == REAL))
    {
        if ((getRealToken(left) != 0) || (getRealToken(right) != 0))
        {
            return newLexeme(INTEGER, "1");
        }
        else
        {
            return newLexeme(INTEGER, "0");
        }
    }
    else
    {
        printf("EVALUATOR: incompatible OR operation.\n");
        exit(1);
    }   
}

LEXEME *
evalAssign(LEXEME *tree, LEXEME *env)
{
    LEXEME *result = eval(getRight(tree), env);
    
    if (getType(getLeft(tree)) == VARIABLE)
    {
        update(getLeft(tree), result, env);
    }

    else if (getType(getLeft(tree)) == DOT)
    {
        LEXEME *object = eval(getLeft(getLeft(tree)), env);
        update(getLeft(getRight(tree)), result, object);
    }

    else
    {
        printf("EVALUATOR: bad ASSIGNMENT\n");
        exit(1);
    }

    return result;
}

LEXEME *
evalDot(LEXEME *tree, LEXEME *env)
{
    LEXEME *object = eval(getLeft(tree), env);
    return eval(getRight(tree), object); // objects == environments!
}

LEXEME *
evalBlock(LEXEME *tree, LEXEME *env)
{
    LEXEME *result;
    while (tree != NULL)
    {
        result = eval(getLeft(tree), env);
        tree = getRight(tree);
    }

    return result;
}

LEXEME *
evalVarDef(LEXEME *tree, LEXEME *env)
{
    insert(getLeft(tree), eval(getRight(getRight(tree)), env), env);
    return getLeft(tree);
}

LEXEME *
evalFuncDef(LEXEME *tree, LEXEME *env)
{
    LEXEME *closure = cons(CLOSURE, env, tree);
    setStringToken(closure, "closure");
    insert(getLeft(getLeft(tree)), closure, env);
    return closure;
}

LEXEME *
evalLambda(LEXEME *tree, LEXEME *env)
{
    LEXEME *closure = cons(CLOSURE, env, tree);
    setStringToken(closure, "closure");
    return closure;
}

LEXEME *
getClosureParams(LEXEME *closure)
{
    return getRight(getLeft(getRight(closure)));
}

LEXEME *
getClosureBody(LEXEME *closure)
{
    return getRight(getRight(closure));
}

LEXEME *
getClosureEnvironment(LEXEME *closure)
{
    return getLeft(closure);
}

LEXEME *
evalPrint(LEXEME *evaluatedArgList)
{
    while (evaluatedArgList != NULL)
    {
        displayLexemeValue(getLeft(evaluatedArgList));
        evaluatedArgList = getRight(evaluatedArgList);
    }

    return evaluatedArgList;
}

LEXEME *
evalFuncCall(LEXEME *tree, LEXEME *env)
{
    LEXEME *name = getLeft(tree);
    LEXEME *args = getRight(tree);
    LEXEME *eargs = evalArgs(args, env);

    if (strcmp(getStringToken(name), "print") == 0)
    {
        return evalPrint(eargs);
    }
    else if (strcmp(getStringToken(name), "getArg") == 0)
    {
        return evalGetArg(eargs);
    }
    else if (strcmp(getStringToken(name), "getArgCount") == 0)
    {
        return evalGetArgCount();
    }
    else if (strcmp(getStringToken(name), "newArray") == 0)
    {
        return evalNewArray(eargs);
    }
    else if (strcmp(getStringToken(name), "getArray") == 0)
    {
        return evalGetArray(eargs);
    }
    else if (strcmp(getStringToken(name), "setArray") == 0)
    {
        return evalSetArray(eargs);
    }
    else if (strcmp(getStringToken(name), "openFileForReading") == 0)
    {
        return evalOpenFileForReading(eargs);
    }
    else if (strcmp(getStringToken(name), "readInteger") == 0)
    {
        return evalReadInteger(eargs);
    }
    else if (strcmp(getStringToken(name), "atFileEnd") == 0)
    {
        return evalAtFileEnd(eargs);
    }
    else if (strcmp(getStringToken(name), "closeFile") == 0)
    {
        return evalCloseFile(eargs);
    }
    else
    {
        LEXEME *closure = eval(name, env);
        LEXEME *params = getClosureParams(closure);
        LEXEME *body = getClosureBody(closure);
        LEXEME *senv = getClosureEnvironment(closure);
        LEXEME *xenv = extend(params, eargs, senv);

        //insert a variable that points to xenv
        insert(newLexeme(VARIABLE,"this"), xenv, xenv);

        return eval(body,xenv);
    }
}

LEXEME *
evalArgs(LEXEME *tree, LEXEME *env)
{
    if (tree == NULL)
    {
        return NULL;
    }
    else
    {
        LEXEME *glue = cons(GLUE, eval(getLeft(tree), env), evalArgs(getRight(tree), env));
        setStringToken(glue, "glue");
        return glue;
    }
}

LEXEME *
evalStatements(LEXEME *tree, LEXEME *env)
{
    if (tree == NULL)
    {
        return NULL;
    }

    else
    {
        LEXEME *glue = cons(GLUE, eval(getLeft(tree), env), evalStatements(getRight(tree), env));
        setStringToken(glue, "glue");
        return glue;
    }
}

LEXEME *
evalWhile(LEXEME *tree, LEXEME *env)
{
    LEXEME *result = eval(getLeft(tree), env);
    LEXEME *block = getRight(tree); 

    if (getIntegerToken(result) == 1)
    {
        block = evalBlock(block, env);
        evalWhile(tree, env);
    }

    return block;
}


LEXEME *
evalIf(LEXEME *tree, LEXEME *env)
{
    LEXEME *expr = eval(getLeft(tree), env);
    if (getIntegerToken(expr) == 1)
    {
        LEXEME *block = evalBlock(getLeft(getRight(tree)), env);
        return block;
    }
    else
    {
        LEXEME *elses = evalElse(getRight(getRight(tree)), env);
        return elses;
    }
}

LEXEME *
evalElse(LEXEME *tree, LEXEME *env)
{
    return eval(getRight(tree), env);
}

LEXEME *
evalReturn(LEXEME *tree, LEXEME *env)
{
    return eval(getRight(tree), env);
}

LEXEME *
evalMoreProgram(LEXEME *tree, LEXEME *env)
{
    if (tree == NULL)
    {
        return NULL;
    }

    else
    {
        eval(getLeft(tree), env);
        return evalMoreProgram(getRight(tree), env);
    }
}

LEXEME *
evalEnd(LEXEME *tree, LEXEME *env)
{
    return eval(getLeft(tree), env);
}

LEXEME *
evalAt(LEXEME *tree, LEXEME *env)
{
    LEXEME *evaluatedArgList = evalArgs(tree, env);
    return evalNewArray(evaluatedArgList);
}

LEXEME *
evalNewArray(LEXEME *evaluatedArgList)
{
    assert(cdr(evaluatedArgList) == NULL);  //ensure only one argument
    LEXEME *size = car(evaluatedArgList);
    assert(getType(size) == INTEGER);          //ensure an integer argument
    LEXEME *a = newLexeme(AT, NULL);
    setAvalToken(a, getIntegerToken(size));  //allocate the array     
    assert(getAvalToken(a) != NULL);                //ensure a good allocation
    return a;
}

LEXEME *
evalGetArrayWrapper(LEXEME *tree, LEXEME *env)
{
    LEXEME *evaluatedArgList = evalArgs(tree, env);
    return evalGetArray(evaluatedArgList);
}

LEXEME *
evalGetArray(LEXEME *evaluatedArgList)
{
    assert(cdr(cdr(evaluatedArgList)) == NULL);
    LEXEME *a = car(evaluatedArgList);
    LEXEME *i = car(cdr(evaluatedArgList));
    
    //check for valid types here
    assert(getType(a) == AT);
    assert(getType(i) == INTEGER);

    LEXEME **aval = getAvalToken(a);
    int index = getIntegerToken(i);
    return aval[index];
}

LEXEME *
evalSetArrayWrapper(LEXEME *tree, LEXEME *env)
{
    LEXEME *evaluatedArgList = evalArgs(tree, env);
    return evalSetArray(evaluatedArgList);
}

LEXEME *
evalSetArray(LEXEME *evaluatedArgList)
{
    assert(cdr(cdr(cdr(evaluatedArgList))) == NULL);
    LEXEME *a = car(evaluatedArgList);
    LEXEME *i = car(cdr(evaluatedArgList));
    LEXEME *v = car(cdr(cdr(evaluatedArgList)));
    
    //check for valid types here
    assert(getType(a) == AT);
    assert(getType(i) == INTEGER);
    assert(getType(v) != NULL);

    LEXEME **aval = getAvalToken(a);
    int index = getIntegerToken(i);
    aval[index] = v;
    return v;                      //could also return the previous value
}

LEXEME *
evalGetArgCount()
{
    LEXEME *count = newLexemeInt(countCL);
    return count;
}

LEXEME *
evalGetArgWrapper(LEXEME *tree, LEXEME *env)
{
    LEXEME *evaluatedArgList = evalArgs(tree, env);
    return evalGetArg(evaluatedArgList);
}

LEXEME *
evalGetArg(LEXEME *evaluatedArgList)
{
    LEXEME *index = car(evaluatedArgList);
    LEXEME *argV = newLexeme(STRING, NULL);
    setStringToken(argV, argsCL[getIntegerToken(index)]);
    return argV;
}

LEXEME *
evalOpenFileForReadingWrapper(LEXEME *tree, LEXEME *env)
{
    LEXEME *evaluatedArgList = evalArgs(tree, env);
    return evalOpenFileForReading(evaluatedArgList);
}

LEXEME *
evalOpenFileForReading(LEXEME *evaluatedArgList)
{
    LEXEME *fileName = car(evaluatedArgList);
    assert(getType(fileName) == STRING);
    LEXEME *fp = newLexeme(FILE_POINTER, NULL);
    setFileToken(fp, fopen(getStringToken(fileName), "r"));
    assert(getFileToken(fp) != NULL);
    return fp;
}

LEXEME *
evalReadIntegerWrapper(LEXEME *tree, LEXEME *env)
{
    LEXEME *evaluatedArgList = evalArgs(tree, env);
    return evalReadInteger(evaluatedArgList);
}

LEXEME *
evalReadInteger(LEXEME *evaluatedArgList)
{
    FILE *filePointer = getFileToken(car(evaluatedArgList));
    assert(filePointer != NULL);
    int buf;
    fscanf(filePointer, "%d", &buf); 
    LEXEME *returnLex = newLexemeInt(buf);
    return returnLex;
}

LEXEME *
evalAtFileEndWrapper(LEXEME *tree, LEXEME *env)
{
    LEXEME *evaluatedArgList = evalArgs(tree, env);
    return evalAtFileEnd(evaluatedArgList);
}

LEXEME *
evalAtFileEnd(LEXEME *evaluatedArgList)
{
    FILE *filePointer = getFileToken(car(evaluatedArgList));
    assert(filePointer != NULL);
    if (feof(filePointer))
    {
        return newLexeme(INTEGER, "1");
    }
    else
    {
        return newLexeme(INTEGER, "0");
    }
}

LEXEME *
evalCloseFileWrapper(LEXEME *tree, LEXEME *env)
{
    LEXEME *evaluatedArgList = evalArgs(tree, env);
    return evalCloseFile(evaluatedArgList);
}

LEXEME *
evalCloseFile(LEXEME *evaluatedArgList)
{
    FILE *filePointer = getFileToken(car(evaluatedArgList));
    assert(filePointer != NULL);
    fclose(filePointer);
    return newLexeme(INTEGER, "1");
}
