/*
 * lexer.c: Tokenize the source file
 *
 * Overview:
 * 1. Get the tokens from the source file
 * 2. Return the tokens
 */

#include "lexer.h"

#include <stdlib.h>

void set_token(char* token, FILE* source);

char** get_tokens(FILE* source) {
  char** tokens = malloc(MAX_TOKENS * sizeof(char*));
  if (tokens == NULL) {
    perror("Error");
    exit(1);
  }
  for (int i = 0; i < MAX_TOKENS; i++) {
    tokens[i] = malloc(MAX_TOKEN_LENGTH * sizeof(char));
    if (tokens[i] == NULL) {
      perror("Error");
      exit(1);
    }
    set_token(tokens[i], source);
  }
  return tokens;
}

void set_token(char* token, FILE* source) {
  for (int i = 0; i < MAX_TOKEN_LENGTH; i++) {
  }
}