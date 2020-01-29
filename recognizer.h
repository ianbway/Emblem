// Ian Braudaway
// Header file for recognizer class

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "lexer.h"
#include "lexeme.h"
#include "types.h"

extern LEXEME *recognize(FILE *filename);