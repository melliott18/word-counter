//-----------------------------------------------------------------------------
// wordlist.c
//
// Implements a list sorted lexicographically with each element of the list
// containing a word and a count.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordlist.h"

// Private Types and Functions ------------------------------------------------

// Node Object
typedef struct NodeObj {
    char *word;
    int count;
    struct NodeObj *next;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// Node constructor
Node newNode(char *s, int size) {
    Node node = malloc(sizeof(NodeObj));
    node->word = calloc(size+1, sizeof(char));
    strncpy(node->word, s, size);
    node->word[size] = '\0';
    node->count = 1;
    node->next = NULL;
    return node;
}

// freeNode()
// Node destructor
void freeNode(Node *ptr) {
    if (ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}

// WordListObj
typedef struct WordListObj {
    Node head;
    int numWords;
} WordListObj;

// find()
// Returns a reference to the Node with string str in WordList.
Node find(WordList list, char *str) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling find() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    Node node = list->head;
    while (node != NULL) {
        if (strcmp(node->word, str) == 0) {
            return node;
        }
        node = node->next;
    }
    return node;
}

// Constructors-Destructors ---------------------------------------------------

// newWordList()
// Word list constructor
WordList newWordList() {
    WordList list = malloc(sizeof(WordListObj));
    list->head = NULL;
    list->numWords = 0;
    return list;
}

// freeWordList()
// Word list destructor
void freeWordList(WordList *ptr) {
    if (ptr != NULL && *ptr != NULL) {
        deleteAll(*ptr);
        free(*ptr);
        *ptr = NULL;
    }
}

// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if WordList list is empty, 0 (false) otherwise.
int isEmpty(WordList list) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling isEmpty() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    return (list->numWords == 0);
}

// wordListSize()
// Returns the number of unique words in the WordList.
int wordListSize(WordList list) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling wordListSize() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    return list->numWords;
}

// check()
// Checks if string str is in WordList.
Node check(WordList list, char *str) {
    Node node = find(list, str);
    return node;
}

// duplicate()
// Increments the count field in Node node.
void duplicate(WordList list, Node node) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling duplicate() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    node->count++;
    return;
}

// add()
// Inserts string str into WordList.
void add(WordList list, char *str, int size) {
    Node node = NULL;
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling add() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    node = check(list, str);

    if (node != NULL) {
        duplicate(list, node);
        return;
    }
    node = newNode(str, size);
    node->next = list->head;
    list->head = node;
    (list->numWords)++;
    return;
}

// deleteAll()
// Reset WordList to the empty state.
void deleteAll(WordList list) {
    Node node = NULL;
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling deleteAll() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }

    while (list->numWords > 0) {
        node = list->head;
        list->head = list->head->next;
        node->next = NULL;
        freeNode(&node);
        list->numWords--;
    }
}

// Other Operations -----------------------------------------------------------

// printWordList()
// Prints all of the words in the WordList along with the number of number of
// occurences of each word.
void printWordList(char *fileName, FILE **out, WordList list) {
    if (*out == NULL) {
        fprintf(stderr, "Error: NULL reference to file %s\n", fileName);
        exit(EXIT_FAILURE);
    }
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling printWordList() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    Node node = list->head;
    while (node != NULL) {
        fprintf(*out, "%s", node->word);
        fprintf(*out, " ");
        fprintf(*out, "%d", node->count);
        fprintf(*out, "\n");
        node = node->next;
    }
}

// getTotalWordCount()
// Returns the total number of words in the WordList.
int getTotalWordCount(WordList list) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling getUniqueWordCount() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    Node node = list->head;
    int totalWordCount = 0;
    while (node != NULL) {
        totalWordCount += node->count;
        node = node->next;
    }
    return totalWordCount;
}

// getCharCount()
// Returns the number of characters in the WordList.
int getCharCount(WordList list) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling getCharCount() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    Node node = list->head;
    int charCount = 0;
    while (node != NULL) {
        charCount += strlen(node->word);
        node = node->next;
    }
    return charCount;  
}

// getShortestWord()
// Returns the shortest word in the WordList.
char *getShortestWord(WordList list) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling getShortestWord() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    Node node = list->head;
    Node shortestWordNode = node;
    int length = strlen(shortestWordNode->word);
    while (node != NULL) {
        if (strlen(node->word) < length) {
            length = strlen(node->word);
            shortestWordNode = node;
        }
        node = node->next;
    }
    return shortestWordNode->word;
}

// getLongestWord()
// Returns the longest word in the WordList.
char *getLongestWord(WordList list) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling getLongestWord() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    Node node = list->head;
    Node longestWordNode = node;
    int length = strlen(longestWordNode->word);
    while (node != NULL) {
        if (strlen(node->word) > length) {
            length = strlen(node->word);
            longestWordNode = node;
        }
        node = node->next;
    }
    return longestWordNode->word;
}

// getAverageWordLength()
// Returns the average word length in the WordList.
int getAverageWordLength(WordList list) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling getAverageWordLength() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    int numWords = wordListSize(list);
    int totalChars = getCharCount(list);
    int averageWordLength = totalChars / numWords;
    return averageWordLength;
}

// getLeastFrequentWord
// Returns the least frequent word in the WordList.
char *getLeastFrequentWord(WordList list) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling getLeastFrequentWord() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    Node node = list->head;
    Node lowestFrequencyNode = node;
    int lowestCount = lowestFrequencyNode->count;
    while (node != NULL) {
        if (node->count < lowestCount) {
            lowestCount = node->count;
            lowestFrequencyNode = node;
        }
        node = node->next;
    }
    return lowestFrequencyNode->word;
}

// getMostFrequentWord
// Returns the most frequent word in the WordList.
char *getMostFrequentWord(WordList list) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling getLeastFrequentWord() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    Node node = list->head;
    Node highestFrequencyNode = node;
    int highestCount = highestFrequencyNode->count;
    while (node != NULL) {
        if (node->count > highestCount) {
            highestCount = node->count;
            highestFrequencyNode = node;
        }
        node = node->next;
    }
    return highestFrequencyNode->word;
}

// getAverageWordFrequency()
// Returns the average frequency of words in the WordList.
int getAverageWordFrequency(WordList list) {
    if (list == NULL) {
        fprintf(stderr,
            "WordList Error: calling getAverageWordFrequency() on NULL WordList reference\n");
        exit(EXIT_FAILURE);
    }
    int totalWordCount = getTotalWordCount(list);
    int uniqueWordCount = wordListSize(list);
    int averageWordFrequency = totalWordCount / uniqueWordCount;
    return averageWordFrequency;
}

Node sortedMerge(Node a, Node b) { 
    Node result = NULL; 
  
    /* Base cases */
    if (a == NULL) {
        return (b); 
    } else if (b == NULL) {
        return (a); 
    }
  
    /* Pick either a or b, and recur */
    if (strcmp(a->word, b->word) <= 0) { 
        result = a; 
        result->next = sortedMerge(a->next, b); 
    } else { 
        result = b; 
        result->next = sortedMerge(a, b->next); 
    } 
    return (result); 
} 

void frontBackSplit(Node source, Node *front, Node *back) { 
    Node fast; 
    Node slow; 
    slow = source; 
    fast = source->next; 
  
    // Advance 'fast' two nodes, and advance 'slow' one node
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
    *front = source; 
    *back = slow->next; 
    slow->next = NULL; 
} 

void mergeSort(Node *headPtr) { 
    Node head = *headPtr; 
    Node a; 
    Node b; 
  
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
  
    // Split the list into two sublists
    frontBackSplit(head, &a, &b); 
  
    // Recursively sort the sublists
    mergeSort(&a); 
    mergeSort(&b); 
  
    // Merge the two sorted lists together
    *headPtr = sortedMerge(a, b); 
} 

// wordListSort()
// Sorts the WordList in alphanumeric order.
void wordListSort(WordList list) { 
    mergeSort(&(list->head));
    return; 
}
