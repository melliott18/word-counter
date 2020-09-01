//-----------------------------------------------------------------------------
// vstring.c
//
// Implements a variable string into which characters can be accumulated, using
// array doubling when the length of the string is exceeded.
//-----------------------------------------------------------------------------

#include "vstring.h"

int vstring(char ch, char *buffer, int index, int *size) {
    if (index == (*size)) {
        buffer = realloc(buffer, (*size) * 2);
        if (buffer == NULL) {
            fprintf(stderr, "Error: buffer memory couldn't be allocated\n");
            exit(EXIT_FAILURE);
        }

        (*size) = (*size) * 2;
    }

    if (ch != ' ') {
        buffer[index] = ch;
    }

    return 0;
}
