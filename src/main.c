#include "common.h"

/* Constants */
const int MAX_TOKENS = 32767;

/* Function prototypes */
FILE *get_source(int argc, string argv[]);
void lex(string tokens[], FILE *source);
void lex_aux(string tokens[], int token_index, FILE *source);
void lex_word(string *token, FILE *source);
void lex_number(string *token, FILE *source);
void lex_quoted(string *token, FILE *source, const char quote);
void lex_symbol(string *token, FILE *source);

/* Entry point */
int main(int argc, string argv[]) {
  FILE *source = get_source(argc, argv);
  string tokens[MAX_TOKENS];
  lex(tokens, source);
  for (int i = 0; tokens[i] != NULL; i++) {
    printf("%s ", tokens[i]);
  }
  printf("\n");
  fclose(source);
  return 0;
}

/* Get source file from compiler arguments */
FILE *get_source(int argc, string argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <source file>\n", argv[0]);
    exit(1);
  }
  FILE *source = fopen(argv[1], "r");
  if (source == NULL) {
    error("Could not open file %s", argv[1]);
  }
  return source;
}

/* Set tokens from source file */
void lex(string tokens[], FILE *source) { lex_aux(tokens, 0, source); }

/* Helper: tail-recursive lexer */
void lex_aux(string tokens[], int token_index, FILE *source) {
  if (token_index >= MAX_TOKENS) {
    error("Reached token limit (%d)", MAX_TOKENS);
  }
  const char first_char = fgetc(source);
  if (first_char == EOF) {
    tokens[token_index] = NULL;
    return;
  }
  if (isspace(first_char)) {
    return lex_aux(tokens, token_index, source);
  }
  ungetc(first_char, source);
  string token = string_new("");
  if (isalpha(first_char) || first_char == '_') {
    lex_word(&token, source);
  } else if (isdigit(first_char)) {
    lex_number(&token, source);
  } else if (first_char == '\'' || first_char == '"') {
    string_join_char(&token, fgetc(source));
    lex_quoted(&token, source, first_char);
  } else {
    lex_symbol(&token, source);
  }
  if (strlen(token) == 0) {
    free(token);
    return lex_aux(tokens, token_index, source);
  }
  tokens[token_index] = token;
  return lex_aux(tokens, token_index + 1, source);
}

/* Set word token (tail-recursive) */
void lex_word(string *token, FILE *source) {
  const char current_char = fgetc(source);
  if (isalnum(current_char) || current_char == '_') {
    string_join_char(token, current_char);
    return lex_word(token, source);
  }
  ungetc(current_char, source);
}

/* Set number token (tail-recursive) */
void lex_number(string *token, FILE *source) {
  const char current_char = fgetc(source);
  if (isalnum(current_char) || current_char == '.') {
    string_join_char(token, current_char);
    return lex_number(token, source);
  }
  ungetc(current_char, source);
}

/* Set quoted token (tail-recursive) */
void lex_quoted(string *token, FILE *source, const char quote) {
  const char first_char = fgetc(source);
  if (first_char == EOF) {
    error("Unexpected end of file");
  }
  const char second_char = fgetc(source);
  if (first_char == '\\') {
    char replacement_char = second_char == 'n'    ? '\n'
                            : second_char == 't'  ? '\t'
                            : second_char == 'r'  ? '\r'
                            : second_char == '\\' ? '\\'
                                                  : second_char;
    string_join_char(token, replacement_char);
    return lex_quoted(token, source, quote);
  }
  ungetc(second_char, source);
  if (first_char == quote) {
    return;
  }
  string_join_char(token, first_char);
  return lex_quoted(token, source, quote);
}

/* Set symbol token */
void lex_symbol(string *token, FILE *source) {
  const string TWO_CHAR_SYMBOLS[] = {"++", "--", "+=", "-=", "*=", "/=", "%=",
                                     "==", "!=", "<=", ">=", "&&", "||", NULL};
  const char first_char = fgetc(source);
  const char second_char = fgetc(source);
  string two_char_token = string_new("");
  string_join_char(&two_char_token, first_char);
  string_join_char(&two_char_token, second_char);
  for (int i = 0; TWO_CHAR_SYMBOLS[i] != NULL; i++) {
    if (string_equals(two_char_token, TWO_CHAR_SYMBOLS[i])) {
      string_join(token, two_char_token);
      free(two_char_token);
      return;
    }
  }
  free(two_char_token);
  if ((first_char == '/' && second_char == '/') || first_char == '#') {
    while (fgetc(source) != '\n');
    return;
  }
  if (first_char == '/' && second_char == '*') {
    while (fgetc(source) != '*' || fgetc(source) != '/');
    return;
  }
  ungetc(second_char, source);
  string_join_char(token, first_char);
}