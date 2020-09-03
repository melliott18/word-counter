//-----------------------------------------------------------------------------
// main.c
//
// Iterates over all of the files specified on the command line, or the
// standard input if none. For each word found in each line, insert into the
// list, updating the count. At end of file, print out all of the words in
// lexicographic order along with the count of the number of times each word
// appears.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "vstring.h"
#include "wordlist.h"

#define BUFFER_SIZE 80

int main(int argc, char *argv[]) {
    FILE *fp;
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));
    char *copy = calloc(BUFFER_SIZE, sizeof(char));
    int ch;
    int size = BUFFER_SIZE;
    int index = 0;
    WordList list = newWordList();

    if (buffer == NULL) {
        fprintf(stderr, "Error: buffer memory couldn't be allocated\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 1) {
        ch = getchar();

        while (ch != '\n' && ch != '\0') {
            if (ch == ' ' || ch == '\t') {
                char *temp = realloc(copy, size+1);
                if (temp != NULL) {
                    copy = temp;
                } else {
                    fprintf(stderr, "Error: buffer memory couldn't be allocated\n");
                    exit(EXIT_FAILURE);
                }
                strncpy(copy, buffer, size);
                copy[size] = '\0';
                add(list, copy, size);
                memset(buffer, 0, size);
                index = 0;
            } else {
                vstring(ch, &buffer, index, &size);
                index++;
            }
            ch = getchar();
        }

        if (ch == '\n' || ch == '\0') {
            copy = realloc(copy, size+1);
            strncpy(copy, buffer, size);
            copy[size] = '\0';
            add(list, copy, size);
        }
    } else {
        int i;

        for (i = 1; i < argc; i++) {
            if ((fp = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, 
                    "Error: file %s could not be opened\n", argv[i]);
                exit(EXIT_FAILURE);
            }

            index = 0;

            while((ch = fgetc(fp)) != EOF) {
                if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0') {
                    char *temp = realloc(copy, size+1);
                    if (temp != NULL) {
                        copy = temp;
                    } else {
                        fprintf(stderr, "Error: buffer memory couldn't be allocated\n");
                        exit(EXIT_FAILURE);
                    }
                    strncpy(copy, buffer, size);
                    copy[size] = '\0';
                    if (copy[0] != '\0') {
                        add(list, copy, size);
                    }
                    memset(buffer, '\0', size);
                    index = 0;
                } else {
                    vstring(ch, &buffer, index, &size);
                    index++;
                }
            }

            if (ch == EOF) {
                char *temp = realloc(copy, size+1);
                if (temp != NULL) {
                    copy = temp;
                } else {
                    fprintf(stderr, "Error: buffer memory couldn't be allocated\n");
                    exit(EXIT_FAILURE);
                }
                strncpy(copy, buffer, size);
                copy[size] = '\0';
                if (copy[0] != '\0') {
                    add(list, copy, size);
                }
            }
            fclose(fp);         
        }
    }
    wordListSort(list);
    printWordList(list);
    freeWordList(&list); 
    return 0;
}
