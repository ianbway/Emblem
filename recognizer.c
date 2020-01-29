// Ian Braudaway
// Implementation file for recognizer class

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "lexer.h"
#include "lexeme.h"
#include "types.h"

LEXER *GlobalLexer;
LEXEME *CurrentLexeme;

static LEXEME *unary();
static LEXEME *operator();
static LEXEME *varExpression();
static bool operatorPending();
static bool expressionPending();
static LEXEME *expression();
static bool statementPending();
static LEXEME *elses();
static LEXEME *ifRule();
static LEXEME *whileRule();
static LEXEME *statement();
static LEXEME *statements();
static LEXEME *block();
static LEXEME *optInit();
static LEXEME *argList();
static LEXEME *optArgList();
static LEXEME *paramList();
static LEXEME *optParamList();
static LEXEME *funcDef();
static LEXEME *varDef();
static LEXEME *def();
static LEXEME *program();
static bool check(char *);
static void advance();
static LEXEME *match(char *);
static void matchNoAdvance(char *);

LEXEME *
unary() 
{ 
    LEXEME *tree;

    if (check(INTEGER)) 
    { 
        return match(INTEGER); 
    }
    else if (check(REAL))
    {
        return match(REAL);
    } 
    else if (check(VARIABLE)) 
    { 
        return varExpression(); 
    }
    else if (check(MINUS))
    {
        match(MINUS);
        tree = unary();
        return cons(UMINUS, NULL, tree);
    } 
    else if (check(NOT))
    {
        match(NOT);
        tree = unary();
        return cons(UNOT, NULL, tree);
    }
    else if (check(STRING))
    {
        return match(STRING);
    }
    else if (check(PRINT))
    {
        match(PRINT);
        match(OPEN_BRACKET);
        tree = argList();
        match(CLOSE_BRACKET);
        return cons(PRINT, NULL, tree);
    }
    else if (check(LAMBDA))
    {
        match(LAMBDA);
        match(OPEN_BRACKET);
        tree = optParamList();
        match(CLOSE_BRACKET);
        LEXEME *bl = block();
        //return cons(LAMBDA, NULL, cons(GLUE, tree, bl));
        return cons(LAMBDA, cons(GLUE, NULL, tree), bl);
    }
    else
    { 
        match(OPEN_BRACKET); 
        tree = expression(); 
        match(CLOSE_BRACKET); 
        return cons(OPEN_BRACKET, NULL, tree);
    }
}

LEXEME *
operator()
{
    if (check(PLUS))
    {
        return match(PLUS);
    }
    else if (check(MINUS))
    {
        return match(MINUS);
    }
    else if (check(MULTIPLY))
    {
        return match(MULTIPLY);
    }
    else if (check(DIVIDE))
    {
        return match(DIVIDE);
    }
    else if (check(LESS_THAN))
    {
        return match(LESS_THAN);
    }
    else if (check(LESS_THAN_EQUAL))
    {
        return match(LESS_THAN_EQUAL);
    }
    else if (check(EQUAL))
    {
        return match(EQUAL);
    }
    else if (check(DOT))
    {
        return match(DOT);
    }
    else if (check(COMPARE_EQUAL))
    {
        return match(COMPARE_EQUAL);
    }
    else if (check(NOT))
    {
        LEXEME *tree;

        tree = match(NOT);
        match(EQUAL);

        return tree;
    }
    else if (check(GREATER_THAN))
    {
        return match(GREATER_THAN);
    }
    else if (check(GREATER_THAN_EQUAL))
    {
        return match(GREATER_THAN_EQUAL);
    }
    else if (check(MODULO))
    {
        return match(MODULO);
    }
    else if (check(OR))
    {
        return match(OR);
    }
    else
    {
        return match(AND);
    }
}

LEXEME *
varExpression() 
{
    LEXEME *tree = NULL;
    LEXEME *v;

    v = match(VARIABLE); 
    if (check(OPEN_BRACKET)) 
    {
        match(OPEN_BRACKET); 
        tree = optArgList();
        match(CLOSE_BRACKET);
        return cons(VARIABLE_EXPR, v, tree); 
    }
    
    return v;
}

bool
operatorPending()
{
    return check(PLUS) || check(MINUS) || check(MULTIPLY) || check(DIVIDE) || 
           check(LESS_THAN) || check(LESS_THAN_EQUAL) || check(EQUAL) || 
           check(NOT) || check(GREATER_THAN) || check(GREATER_THAN_EQUAL) ||
           check(MODULO) || check(OR) || check(AND) || check(COMPARE_EQUAL)
           || check(DOT);
}

bool
expressionPending()
{
    return check(INTEGER) || check(REAL) || check(VARIABLE) || 
           check(MINUS) || check(NOT) || check(STRING) || check(OPEN_BRACKET) ||
           check(AT) || check(PRINT);
}

LEXEME * 
expression() 
{ 
    LEXEME *u;
    LEXEME *o;
    LEXEME *e;

    u = unary(); 
    if (operatorPending()) 
    { 
        o = operator();
        e = expression(); 
        return cons(getType(o),u,e);
    }
    else
    {
       return u;
    }
}

bool
statementPending()
{
    return check(IF) || check(WHILE) || check(FUNC) || check(VAR) || 
           check(RETURN) || expressionPending();
}

LEXEME *
elses()
{
    LEXEME *ir;
    LEXEME *bl;

    if (check(ELSE))
    {
        match(ELSE);
        if (check(IF))
        {
            ir = ifRule();
            return cons(ELSE, NULL, ir);
        }
        else
        {
            bl = block();
            return cons(ELSE, NULL, bl);
        }
    }

    else
    {
        return NULL;
    }
}

LEXEME *
ifRule()
{
    LEXEME *e;
    LEXEME *bl;

    match(IF);
    match(OPEN_BRACKET);
    e = expression();
    match(CLOSE_BRACKET);
    bl = block();

    return cons(IF, e, cons(IFJOIN, bl, elses()));
}

LEXEME *
whileRule()
{
    LEXEME *e;

    match(WHILE);
    match(OPEN_BRACKET);
    e = expression();
    match(CLOSE_BRACKET);

    return cons(WHILE, e, block());
}

LEXEME *
statement()
{
    if (expressionPending())
    {
        return expression();
    }
    else if (check(IF))
    {
        return ifRule();
    }
    else if (check(WHILE))
    {
        return whileRule();
    }
    else if (check(FUNC))
    {
        return funcDef();
    }
    else if (check(VAR))
    {
        return varDef();
    }
    else
    {
        match(RETURN);
        return cons(RETURN, NULL, expression());
    }
}

LEXEME *
statements()
{
    LEXEME *st;
    LEXEME *sts = NULL;

    st = statement();
    if (statementPending())
    {
        sts = statements();
    }

    return cons(STATEMENTS, st, sts);
}

LEXEME *
block()
{
    LEXEME *sts;

    match(OPEN_BLOCK);
    sts = statements();
    match(CLOSE_BLOCK);

    return cons(OPEN_BLOCK, NULL, sts);
}

LEXEME *
optInit()
{
    if (check(EQUAL))
    {
        match(EQUAL);
        return cons(EQUAL, NULL, expression());
    }
    else
    {
        return NULL;
    }
}

LEXEME *
argList()
{
    LEXEME *e;

    e = expression();

    if (check(BAR))
    {
        match(BAR);
        return cons(ARGLIST, e, argList());
    }
    else
    {
        return cons(ARGLIST, e, NULL);
    }
}

LEXEME *
optArgList()
{
    if (expressionPending())
    {
        return argList();
    }
    else
    {
        return NULL;
    }
}

LEXEME *
paramList()
{
    LEXEME *v;

    v = match(VARIABLE);
    if (check(BAR))
    {
        match(BAR);
        return cons(PARAMLIST, v, paramList());
    }
    else
    {
        return cons(PARAMLIST, v, NULL);
    }

}

LEXEME *
optParamList()
{
    if (check(VARIABLE))
    {
        return paramList();
    }
    else
    {
        return NULL;
    }
}

LEXEME *
funcDef()
{
    LEXEME *f;
    LEXEME *id;

    match(FUNC);
    id = match(VARIABLE);
    match(OPEN_BRACKET);
    f = cons(FUNCDEF, id, optParamList());
    match(CLOSE_BRACKET);

    return cons(FUNC, f, block());
}

LEXEME *
varDef()
{
    LEXEME *id;

    match(VAR);
    id = match(VARIABLE);
    return cons(VAR, id, optInit());
}

LEXEME *
def()
{
    if (check(VAR))
    {
        return varDef();
    }
    else
    {
        return funcDef();
    }
}

LEXEME *
program()
{
    LEXEME *d;
    LEXEME *st;

    if (check(FUNC) || check(VAR)) 
    {
        d = def();
        if (!check(ENDofINPUT))
        { 
            return cons(MOREPROGRAM, d, program());
        }
        else
        {
            match(ENDofINPUT);
            return cons(ENDofINPUT, d, NULL);
        }
    }
    else
    {
        st = statement();
        match(ENDofINPUT);
        return cons(ENDofINPUT, st, NULL);
    }
}

bool 
check(char *type) 
{ 
    return getType(CurrentLexeme) == type; 
}

void 
advance() 
{ 
    CurrentLexeme = lex(GlobalLexer); 
} 

LEXEME * 
match(char *type) 
{
    LEXEME *matchLex;

    matchNoAdvance(type); 

    matchLex = CurrentLexeme;

    advance(); 

    return matchLex;
}

void 
matchNoAdvance(char *type)
{
    if (!check(type))
    {
        fprintf(stdout," illegal\n current lexeme: %s\n recognize error: %s\n line number: %d\n", 
                getType(CurrentLexeme), type, getLineNumber(GlobalLexer)); 
        exit(1);
    }
}

LEXEME *
recognize(FILE *fileName)
{
    GlobalLexer = newLexer(fileName);

    CurrentLexeme = lex(GlobalLexer); 
    LEXEME *tree = program(); 

    // legal

    return tree;
}