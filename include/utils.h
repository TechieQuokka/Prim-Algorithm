#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define INF 999999

void* safe_malloc(size_t size);
void safe_free(void **ptr);
void error_exit(const char* message);
void debug_print(const char* format, ...);

#endif