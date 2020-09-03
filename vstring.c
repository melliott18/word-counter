//-----------------------------------------------------------------------------
// vstring.c
//
// Implements a variable string into which characters can be accumulated, using
// array doubling when the length of the string is exceeded.
//-----------------------------------------------------------------------------

#include "vstring.h"

int vstring(char ch, char **buffer, int index, int *size) {
    //printf("%d\n", index);
    if (index == (*size)) {
        //printf("%d\n", *size);
        (*size) = (*size) * 2;
        //printf("%d\n", *size);
        char *temp = realloc(*buffer, *size);
        if (temp != NULL) {
            *buffer = temp;
        } else {
            fprintf(stderr, "Error: buffer memory couldn't be allocated\n");
            exit(EXIT_FAILURE);
        }
    }

    if (ch != ' ' && index < (*size)) {
        (*buffer)[index] = ch;
    }

    return 0;
}
