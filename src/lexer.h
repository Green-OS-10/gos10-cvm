#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define MAX_TOKENS 10000
#define MAX_TOKEN_LENGTH 100

char** get_tokens(FILE* source);

#endif  // LEXER_H
