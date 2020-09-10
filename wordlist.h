//-----------------------------------------------------------------------------
// wordlist.h
//
// Implements a list sorted lexicographically with each element of the list
// containing a word and a count.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _WORDLIST_H_
#define _WORDLIST_H_

// WordList 
typedef struct WordListObj *WordList;

// Constructors-Destructors ---------------------------------------------------

// newWordList()
// Constructor for the WordList type.
WordList newWordList();

// freeWordList()
// Destructor for the WordList type.
void freeWordList(WordList *ptr);

// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if WordList list is empty, 0 (false) otherwise.
int isEmpty(WordList list);

// wordListSize()
// Returns the number of unique words in the WordList.
int wordListSize(WordList list);

// add()
// Inserts string str into WordList.
void add(WordList list, char *str, int size);

// deleteAll()
// Reset WordList to the empty state.
void deleteAll(WordList list);

// Other Operations -----------------------------------------------------------

// printWordList()
// Prints all of the words in the WordList along with the number of number of
// occurences of each word.
void printWordList(char *fileName, FILE **out, WordList list);

// getTotalWordCount()
// Returns the total number of words in the WordList.
int getTotalWordCount(WordList list);

// getCharCount()
// Returns the number of characters in the WordList.
int getCharCount(WordList list);

// getShortestWord()
// Returns the shortest word in the WordList.
char *getShortestWord(WordList list);

// getLongestWord()
// Returns the longest word in the WordList.
char *getLongestWord(WordList list);

// getAverageWordLength()
// Returns the average word length in the WordList.
int getAverageWordLength(WordList list);

// getLeastFrequentWord()
// Returns the least frequent word in the WordList.
char *getLeastFrequentWord(WordList list);

// getMostFrequentWord()
// Returns the most frequent word in the WordList.
char *getMostFrequentWord(WordList list);

// getAverageWordFrequency()
// Returns the average frequency of words in the WordList.
int getAverageWordFrequency(WordList list);

// wordListSort()
// Sorts the WordList in alphanumeric order.
void wordListSort(WordList list);

#endif
