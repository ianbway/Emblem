// Ian Braudaway
// Implementation file for environment

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "lexeme.h"
#include "types.h"
#include "environment.h"

static LEXEME *treeWalkerHelper(LEXEME *, LEXEME *);

LEXEME *
car(LEXEME *lex)
{
    return getLeft(lex);
}

LEXEME *
cdr(LEXEME *lex)
{
    return getRight(lex);
}

void
setCar(LEXEME *lex, LEXEME *newLeft)
{
    setLeft(lex, newLeft);
}

void
setCdr(LEXEME *lex, LEXEME *newRight)
{
    setRight(lex, newRight);
}

LEXEME *
create()
{
    //return cons(ENV, NULL, cons(VALUES, NULL, NULL));
    return extend(NULL, NULL, NULL);
}

LEXEME *
treeWalkerHelper(LEXEME *variable, LEXEME *env)
{
    while (env != NULL)
    {
        LEXEME *vars = car(env);
        LEXEME *vals = car(cdr(env));
        while (vars != NULL)
        {
            if (strcmp(getStringToken(variable), getStringToken(car(vars))) == 0)
            {
                return vals;
            }
            
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = cdr(cdr(env));
    }
    fprintf(stdout,"FATAL variable: %s is undefined.\n", getStringToken(variable)); 
    exit(1); 
    return NULL;
}

LEXEME *
lookup(LEXEME *variable, LEXEME *env)
{
    return car(treeWalkerHelper(variable, env));
}

void
update(LEXEME *variable, LEXEME *values, LEXEME *env)
{
    setCar(treeWalkerHelper(variable, env), values);
    return;
}

LEXEME *
insert(LEXEME *variable, LEXEME *value, LEXEME *env)
{
    setCar(env, cons(JOIN, variable, car(env)));
    setCar(cdr(env), cons(JOIN, value, car(cdr(env))));
    return value;
}

LEXEME *
extend(LEXEME *variables, LEXEME *values, LEXEME *env)
{
    LEXEME *result = cons(ENV, variables, cons(ENV, values, env));
    setStringToken(result, ENV); 
    return result;
}

void
displayEnvironment(LEXEME *env, bool lt)
{
    int envCount = 0;

    if (lt)
    {
        fprintf(stdout, "The local environment is:\n");
    }

    else
    {
        fprintf(stdout, "The environment is:\n");
    }

    while (env != NULL)
    {
        fprintf(stdout, "Scope Level = %d\n", envCount);

        LEXEME *vars = car(env);
        LEXEME *vals = car(cdr(env));
        while (vars != NULL)
        {
            printf(" %s : ", getStringToken(car(vars)));
            displayLexemeValue(car(vals));
            vars = cdr(vars);
            vals = cdr(vals);
        }
        if (lt)
        {
            break;
        }
        envCount = envCount + 1;
        env = cdr(cdr(env));
    }
    fprintf(stdout, "\n");
}