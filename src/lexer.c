/*
 * lexer.c: Tokenize the source file
 *
 * Overview:
 * 1. Get the tokens from the source file
 * 2. Return the tokens
 */

#include "lexer.h"

#include <ctype.h>
#include <stdlib.h>

int set_token(char* token, FILE* source);
int set_token_word(char* token, FILE* source);
int set_token_number(char* token, FILE* source);
int set_token_string(char* token, FILE* source);
int set_token_symbol(char* token, FILE* source);

typedef enum { WORD = 1, NUMBER, STRING, SYMBOL } token_type;

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
    int result = set_token(tokens[i], source);
    if (result == EOF) {
      tokens[i] = NULL;
      break;
    }
  }
  return tokens;
}

int set_token(char* token, FILE* source) {
  int c = fgetc(source);
  while (isspace(c)) {
    c = fgetc(source);
  }
  if (c == EOF) {
    return EOF;
  }
  token_type type = isalpha(c)   ? WORD
                    : isdigit(c) ? NUMBER
                    : c == '"'   ? STRING
                                 : SYMBOL;
  ungetc(c, source);
  return type == WORD     ? set_token_word(token, source)
         : type == NUMBER ? set_token_number(token, source)
         : type == STRING ? set_token_string(token, source)
                          : set_token_symbol(token, source);
}

int set_token_word(char* token, FILE* source) {
  int i = 0;
  char c = fgetc(source);
  while (isalnum(c) || c == '_') {
    token[i++] = c;
    c = fgetc(source);
  }
  ungetc(c, source);
  token[i] = '\0';
  return c;
}

int set_token_number(char* token, FILE* source) {
  int i = 0;
  char c = fgetc(source);
  while (isdigit(c) || c == '.') {
    token[i++] = c;
    c = fgetc(source);
  }
  ungetc(c, source);
  token[i] = '\0';
  return c;
}

int set_token_string(char* token, FILE* source) {
  int i = 0;
  char c = fgetc(source);
  while (c == '"') {
    token[i++] = c;
    c = fgetc(source);
  }
  ungetc(c, source);
  token[i] = '\0';
  return c;
}

int set_token_symbol(char* token, FILE* source) {
  char c = fgetc(source);
  token[0] = c;
  token[1] = '\0';
  return c;
}