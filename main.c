//-----------------------------------------------------------------------------
// main.c
//
// Iterates over all of the files specified on the command line, or the
// standard input if none. For each word found in each line, insert into the
// list, updating the count. At end of file, print out all of the words in
// lexicographic order along with the count of the number of times each word
// appears.
//-----------------------------------------------------------------------------

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "vstring.h"
#include "wordlist.h"

#define BUFFER_SIZE 80
#define OPTIONS "svi:o:"

void extractWords(char *fileName, FILE **in, WordList *list) {
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));
    char *copy = calloc(BUFFER_SIZE, sizeof(char));
    int ch;
    int index = 0;
    int size = BUFFER_SIZE;

    if (*in == NULL) {
        fprintf(stderr, "Error: NULL reference to file %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    index = 0;

    while((ch = fgetc(*in)) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0') {
            char *temp = realloc(copy, size+1);
            if (temp != NULL) {
                copy = temp;
            } else {
                fprintf(stderr, 
                    "Error: buffer memory couldn't be allocated\n");
                exit(EXIT_FAILURE);
            }
            strncpy(copy, buffer, size);
            copy[size] = '\0';
            if (copy[0] != '\0') {
                add(*list, copy, size);
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
            add(*list, copy, size);
        }
    }

    fclose(*in);
    return;
}

int main(int argc, char *argv[]) {
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));
    char *copy = calloc(BUFFER_SIZE, sizeof(char));
    char *fileName;
    FILE *in = stdin;
    FILE *out = stdout;
    int ch;
    int index = 0;
    int option = 0;
    int size = BUFFER_SIZE;
    int sort = 0;
    int verbose = 0;
    WordList list = newWordList();

    if (buffer == NULL) {
        fprintf(stderr, "Error: buffer memory couldn't be allocated\n");
        exit(EXIT_FAILURE);
    }

    // getopt()
    while ((option = getopt(argc, argv, OPTIONS)) != -1) {
        switch (option) {
            case 's': // Sort option
                sort = 1;
                break;
            case 'v': // Verbose option
                verbose = 1;
                break;
            case 'i': // Sets the input file (default is stdin)
                if ((in = fopen(optarg, "r")) == NULL) {
                    fprintf(stderr, "Error: file %s could not be opened\n", optarg);
                    exit(EXIT_FAILURE);
                }
                extractWords(optarg, &in, &list);
                break;
            case 'o': // Sets the output file (default is stdout)
                if ((out = fopen(optarg, "w")) == NULL) {
                    fprintf(stderr, "Error: file %s could not be opened\n", optarg);
                    exit(EXIT_FAILURE);
                }
                fileName = optarg;
                break;
            default:
              printf("%s\n", "Error: invalid argument!");
              exit(EXIT_FAILURE);
        }
    }

    if (in == stdin) {
        ch = getchar();

        while (ch != '\n' && ch != '\0') {
            if (ch == ' ' || ch == '\t') {
                char *temp = realloc(copy, size+1);
                if (temp != NULL) {
                    copy = temp;
                } else {
                    fprintf(stderr, 
                        "Error: buffer memory couldn't be allocated\n");
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
    }

    if (sort) {
        wordListSort(list);
    }

    printWordList(fileName, &out, list);

    if (verbose) {
        printf("\n");
        int numTotalWords = getTotalWordCount(list);
        printf("Total number of words: %d\n", numTotalWords);
        int numUniqueWords = wordListSize(list);
        printf("Number of unique words: %d\n", numUniqueWords);
        int numChars = getCharCount(list);
        printf("Total number of characters: %d\n", numChars);
        char *shortestWord = getShortestWord(list);
        printf("Shortest word: %s\n", shortestWord);
        //printf("Shortest word length: %lu\n", strlen(shortestWord));
        char *longestWord = getLongestWord(list);
        printf("Longest word: %s\n", longestWord);
        //printf("Longest word length: %lu\n", strlen(longestWord));
        int averageWordLength = getAverageWordLength(list);
        printf("Average word length: %d\n", averageWordLength);
        char *leastFrequentWord = getLeastFrequentWord(list);
        printf("Least frequent word: %s\n", leastFrequentWord);
        char *mostFrequentWord = getMostFrequentWord(list);
        printf("Most frequent word: %s\n", mostFrequentWord);
        //printf("Least frequent word frequency: %lu\n", leastFrequentWord->count);
        //char *longestWord = getLongestWord(list);
        //printf("Longest word: %s\n", longestWord);
        //printf("Longest word length: %lu\n", strlen(longestWord));
        int averageWordFrequency = getAverageWordFrequency(list);
        printf("Average word frequency: %d\n", averageWordFrequency);
    }

    freeWordList(&list);
    fclose(out);
    return 0;
}
