#include "common.h"

/* Error handling */
void error(string message, ...) {
  va_list args;
  va_start(args, message);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, message, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

int string_equals(string a, string b) { return strcmp(a, b) == 0; }

string string_new(string src) {
  const size_t size = strlen(src);
  string dest = malloc(size + 1);
  if (dest == NULL) {
    error("Out of memory");
  }
  memccpy(dest, src, '\0', size);
  return dest;
}

void string_set(string *dest, string src) {
  const size_t size = strlen(src);
  *dest = realloc(*dest, size + 1);
  if (dest == NULL) {
    error("Out of memory");
  }
  memccpy(*dest, src, '\0', size);
}

void string_join(string *dest, string src) {
  const size_t dest_size = strlen(*dest);
  const size_t src_size = strlen(src);
  *dest = realloc(*dest, dest_size + src_size + 1);
  if (dest == NULL) {
    error("Out of memory");
  }
  memccpy(*dest + dest_size, src, '\0', src_size);
}

void string_join_char(string *dest, char src) {
  const size_t size = strlen(*dest) + 1;
  *dest = realloc(*dest, size + 1);
  if (dest == NULL) {
    error("Out of memory");
  }
  (*dest)[size - 1] = src;
  (*dest)[size] = '\0';
}