#include "common.h"

/* Helper: error handling */
void error(string message, ...) {
  va_list args;
  va_start(args, message);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, message, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

/* Helper: string allocation
 * Note: to save memory, call strfit() after the string is set
 */
string strnew() {
  string ptr = calloc((MAX_STRING_LENGTH + 1), sizeof(char));
  if (ptr == NULL) {
    error("Out of memory");
  }
  return ptr;
}

/* Helper: string re-allocation */
string strfit(string src) {
  const int size = strlen(src);
  if (size > MAX_STRING_LENGTH) {
    error("Reached string length limit (%d)", MAX_STRING_LENGTH);
  }
  string ptr = realloc(src, (size + 1) * sizeof(char));
  if (ptr == NULL) {
    error("Out of memory");
  }
  return ptr;
}