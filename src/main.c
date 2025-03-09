/*
 * main.c: Entry point for the compiler
 *
 * Overview:
 * 1. Get the source file
 * 2. Get the tokens from the source file
 * 3. Print the tokens
 */

#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "lexer.h"

int main(int argc, char *argv[]) {
  FILE *source = get_source(argc, argv);
  char **tokens = get_tokens(source);
  for (int i = 0; i < MAX_TOKENS; i++) {
    if (tokens[i] == NULL) {
      break;
    }
    printf("(%s)\n", tokens[i]);
    free(tokens[i]);
  }
  free(tokens);
  fclose(source);
  return 0;
}