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
    char *copy = calloc(2, sizeof(char));
    char *word;
    const char *delimiter_characters = " \t\n";
    WordList wl = newWordList();
    char ch;
    int size;
    int i, j;

    if (buffer == NULL) {
        fprintf(stderr, "Error: buffer memory couldn't be allocated\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 1) {
        size = 2;
        i = j = 0;
        ch = getchar();

        while (ch != '\n' && ch != '\0') {
            vstring(ch, buffer, i, &size);
            if (ch == ' ') {
                copy = realloc(copy, size+1);
                strncpy(copy, buffer, size);
                copy[size] = '\0';
                add(wl, copy, size);
                memset(buffer, 0, size);
                i = 0;
            } else {
                i++;
            }
            ch = getchar();
        }

        if (ch == '\n' || ch == '\0') {
            copy = realloc(copy, size+1);
            strncpy(copy, buffer, size);
            copy[size] = '\0';
            add(wl, copy, size);
        }

        wordListSort(wl);
        printWordList(wl);
        freeWordList(&wl);
    } else {
        for (i = 1; i < argc; i++) {
            if ((fp = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "Error: file %s could not be opened\n", argv[i]);
                exit(EXIT_FAILURE);
            }

            // Read each line into the buffer
            while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
                word = strtok(buffer, delimiter_characters);
                while (word != NULL) {
                    if (word != NULL) {
                        size = strlen(word);
                    }
                    add(wl, word, size);
                    word = strtok(NULL, delimiter_characters);
                }

            }
            fclose(fp);
        }
        wordListSort(wl);
        printWordList(wl);
        freeWordList(&wl);
    }

    return 0;
}
