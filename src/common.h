#ifndef COMMON_H
#define COMMON_H

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *string;

void error(string message, ...);
int string_equals(string a, string b);
string string_new(string src);
void string_set(string *dest, string src);
void string_join(string *dest, string src);
void string_join_char(string *dest, char src);

#endif  // COMMON_H