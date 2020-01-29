// Ian Braudaway
// Header file for evaluator

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "lexer.h"
#include "lexeme.h"
#include "types.h"
#include "recognizer.h"
#include "environment.h"

extern LEXEME *eval(LEXEME *, LEXEME *);