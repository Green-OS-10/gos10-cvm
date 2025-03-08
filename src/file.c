#include "file.h"

#include <stdlib.h>

FILE *get_source(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <source>.c\n", argv[0]);
    exit(1);
  }
  FILE *source = fopen(argv[1], "r");
  if (source == NULL) {
    perror("Error");
    exit(1);
  }
  return source;
}