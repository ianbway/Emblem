// Ian Braudaway
// Header file for lexeme class

#ifndef __LEXEME_INCLUDED__
#define __LEXEME_INCLUDED__

#include <stdio.h>
#include <stdlib.h>

typedef struct LEXEME LEXEME;

extern LEXEME *newLexeme(char *, char *);
extern LEXEME *newLexemeInt(int integer);
extern LEXEME *newLexemeReal(double real);
extern LEXEME *newLexemeString(char *string);
extern LEXEME *cons(char *, LEXEME *, LEXEME *);
extern char *getType(LEXEME *);
extern char *getStringToken(LEXEME *);
extern int getIntegerToken(LEXEME *);
extern double getRealToken(LEXEME *);
extern LEXEME **getAvalToken(LEXEME *);
extern FILE *getFileToken(LEXEME *);
extern LEXEME *getLeft(LEXEME *);
extern LEXEME *getRight(LEXEME *);
extern void setLeft(LEXEME *, LEXEME *);
extern void setRight(LEXEME *, LEXEME *);
extern void setStringToken(LEXEME *, char *);
extern void setIntegerToken(LEXEME *, int setToThis);
extern void setRealToken(LEXEME *, double setToThis);
extern void setAvalToken(LEXEME *, int slots);
extern void setFileToken(LEXEME *, FILE *);
extern void display(LEXEME *);
extern void displayLexemeValue(LEXEME *);

#endif