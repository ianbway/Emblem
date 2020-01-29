// Ian Braudaway
// Header file for environment

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "lexeme.h"
#include "types.h"

// extern LEXEME *cons(char *, LEXEME *, LEXEME *);
extern LEXEME *car(LEXEME *);
extern LEXEME *cdr(LEXEME *);
extern void setCar(LEXEME *, LEXEME *);
extern void setCdr(LEXEME *, LEXEME *);

extern LEXEME *create();
extern LEXEME *lookup(LEXEME *, LEXEME *);
extern void update(LEXEME *, LEXEME *, LEXEME *);
extern LEXEME *insert(LEXEME *, LEXEME *, LEXEME *);
extern LEXEME *extend(LEXEME *, LEXEME *, LEXEME *);
extern void displayEnvironment(LEXEME *, bool lt);