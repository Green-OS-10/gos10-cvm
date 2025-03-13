#ifndef COMMON_H
#define COMMON_H

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 255

/* String macros for convenience
 * Note: these are not safe for production use but they will do for now
 */
#define streq(a, b) (strcmp(a, b) == 0)
#define strcatc(a, b) (strcat(a, (char[]){b, '\0'}))

void error(char *message, ...);
char *strnew();
char *strfit(char *src);

#endif  // COMMON_H