#include "utils.h"

void* safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        error_exit("Memory allocation failed");
    }
    return ptr;
}

void safe_free(void **ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

void error_exit(const char* message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

void debug_print(const char* format, ...) {
    #ifdef DEBUG
    va_list args;
    va_start(args, format);
    printf("DEBUG: ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
    #else
    (void)format;
    #endif
}