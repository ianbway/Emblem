// Ian Braudaway
// Implementation file for lexer class

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "lexeme.h"
#include "lexer.h"
#include "types.h"

struct LEXER
{
    FILE *file;
    int lineNumber;
};

LEXER *
newLexer(FILE *fp)
{
    LEXER *lex = malloc(sizeof(LEXER));
    if (lex == 0) 
    { 
        fprintf(stderr,"out of memory\n"); 
        exit(1); 
    }

    lex->file = fp;
    lex->lineNumber = 1;

    return lex;
}

int
getLineNumber(LEXER *lex)
{
    return lex->lineNumber;
}

void 
skipWhiteSpace(LEXER *lex)
{
    char ch;

    ch = fgetc(lex->file);
    while (isspace(ch) || (ch == '#'))
    {
        if (ch == '\n')
        {
            lex->lineNumber = lex->lineNumber + 1;
        }

        if (ch == '#')
        {
            ch = fgetc(lex->file);
            while (ch != '#')
            {
                if (ch == '\n')
                {
                    lex->lineNumber = lex->lineNumber + 1;
                }

                ch = fgetc(lex->file);
            }
        }

        ch = fgetc(lex->file);
    }

    // the character that got us out of the loop was NOT whitespace
    // so we need to push it back so it can be read again.

    ungetc(ch, lex->file);
}

LEXEME *
lexVariableOrKeyword(LEXER *lex)
{
    char ch;
    int length = 32;
    int index = 0;    
    char *token = malloc(sizeof(char) * length + 1);   // + 1 for the null byte

    ch = fgetc(lex->file);
    while (((!feof(lex->file)) && (isalpha(ch))) || (isdigit(ch)))
    {
        if (index == length)
        {
            token = realloc(token,sizeof(char) * length * 2 + 1);
            length *= 2;
        }
        token[index++] = ch;
        token[index] = '\0';
        ch = fgetc(lex->file);
    }

    //push back the character that got us out of the loop
    //it may be some kind of punctuation

    ungetc(ch, lex->file);

    //token holds either a variable or a keyword, so figure it out

    if (strcmp(token,"if") == 0) 
        return newLexeme(IF, NULL);
    else if (strcmp(token,"else") == 0) 
        return newLexeme(ELSE, NULL);
    else if (strcmp(token,"while") == 0) 
        return newLexeme(WHILE, NULL);
    else if (strcmp(token,"var") == 0) 
        return newLexeme(VAR, NULL);
    else if (strcmp(token,"func") == 0) 
        return newLexeme(FUNC, NULL);
    else if (strcmp(token,"lambda") == 0) 
        return newLexeme(LAMBDA, NULL);
    else if (strcmp(token,"return") == 0) 
        return newLexeme(RETURN, NULL);
    else if (strcmp(token,"or") == 0) 
        return newLexeme(OR, NULL);
    else if (strcmp(token,"and") == 0) 
        return newLexeme(AND, NULL);
        //more keyword testing here
    else //must be a variable!
        return newLexeme(VARIABLE,token);
}

LEXEME *
lexNumber(LEXER *lex)
{
    int real = 0;
    char ch;
    int length = 32;
    int index = 0;    
    char *token = malloc(sizeof(char) * length + 1);   // + 1 for the null byte

    ch = fgetc(lex->file);
    while ((!feof(lex->file) && (isdigit(ch))) || (ch == '.'))
    {
        if (ch == '.' && real)
        {
            fprintf(stdout,"BAD NUMBER: %c , line number : %d \n", ch, lex->lineNumber); 
            exit(1);
        }

        if (ch == '.')
        {
            real = 1;
        }

        if (index == length)
        {
            token = realloc(token,sizeof(char) * length * 2 + 1);
            length *= 2;
        }
        token[index++] = ch;
        token[index] = '\0';

        ch = fgetc(lex->file);
    }
    ungetc(ch, lex->file);

    if (real)
    {
        return newLexeme(REAL, token);
    }

    else
    {
        return newLexeme(INTEGER, token);
    }
}

LEXEME *
lexString(LEXER *lex)
{
    char ch;
    int length = 32;
    int index = 0;    
    char *token = malloc(sizeof(char) * length + 1);   // + 1 for the null byte

    ch = fgetc(lex->file);
    while ((!feof(lex->file) && (ch != '\"')))
    {
        if (index == length)
        {
            token = realloc(token,sizeof(char) * length * 2 + 1);
            length *= 2;
        }
        token[index++] = ch;
        token[index] = '\0';

        ch = fgetc(lex->file);
    }

    return newLexeme(STRING, token);
}

LEXEME *
lex(LEXER *lex)
{
    char ch;
    char next;

    skipWhiteSpace(lex);

    ch = fgetc(lex->file); 

    if (lex->file == NULL)
    {
        return newLexeme(ENDofINPUT, NULL); 
    }

    switch(ch) 
    { 
        // single character tokens 

        case '[': return newLexeme(OPEN_BRACKET, NULL);
        case ']': return newLexeme(CLOSE_BRACKET, NULL);
        case ':': return newLexeme(OPEN_BLOCK, NULL);
        case ';': return newLexeme(CLOSE_BLOCK, NULL);
        case '|': return newLexeme(BAR, NULL); 
        case '+': return newLexeme(PLUS, NULL); //what about ++ and += ?
        case '*': return newLexeme(MULTIPLY, NULL); 
        case '-': return newLexeme(MINUS, NULL);
        case '/': return newLexeme(DIVIDE, NULL); 
        case '<': 
            next = fgetc(lex->file);
            if (next == '=')
            {
                return newLexeme(LESS_THAN_EQUAL, NULL);
            }

            else
            {
                ungetc(next, lex->file);
                return newLexeme(LESS_THAN, NULL);
            } 

        case '>': 
            next = fgetc(lex->file);
            if (next == '=')
            {
                return newLexeme(GREATER_THAN_EQUAL, NULL);
            }

            else
            {
                ungetc(next, lex->file);
                return newLexeme(GREATER_THAN, NULL);
            }

        case '=': 
            next = fgetc(lex->file);
            if (next == '=')
            {
                return newLexeme(COMPARE_EQUAL, NULL);
            }

            else
            {
                ungetc(next, lex->file);
                return newLexeme(EQUAL, NULL);
            } 
            
        case '.': return newLexeme(DOT, NULL);
        case '@': return newLexeme(AT, NULL);
        case '%': return newLexeme(MODULO, NULL);
        case '!': return newLexeme(NOT, NULL);

        //add any other cases here

        default: 
        // multi-character tokens (only numbers, 
        // variables/keywords, and strings) 
            if (isdigit(ch)) 
            { 
                ungetc(ch, lex->file); 
                return lexNumber(lex); 
            } 
            else if (isalpha(ch)) 
            { 
                ungetc(ch, lex->file); 
                return lexVariableOrKeyword(lex);
            } 
            else if (ch == '\"') 
            { 
                return lexString(lex); 
            }
            else if (feof(lex->file))
            {
                return newLexeme(ENDofINPUT, NULL); 
            } 
            else
                //need line #
                fprintf(stdout,"UNKNOWN CHARACTER: %c , line number : %d \n", ch, lex->lineNumber); 
                exit(1);  
    } 
}