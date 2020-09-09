//-----------------------------------------------------------------------------
// wordlist.h
//
// Implements a list sorted lexicographically with each element of the list
// containing a word and a count.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _wordlist_H_INCLUDE_
#define _wordlist_H_INCLUDE_

// WordList 
typedef struct WordListObj* WordList;


// Constructors-Destructors ---------------------------------------------------


// newWordList()
// Constructor for the WordList type.
WordList newWordList();

// freeWordList()
// Destructor for the WordList type.
void freeWordList(WordList* ptr);


// ADT operations -------------------------------------------------------------


// isEmpty()
// Returns 1 (true) if WordList list is empty, 0 (false) otherwise.
int isEmpty(WordList list);

// listSize()
// Returns the number of elements in list.
int listSize(WordList list);

// add()
// Inserts string str into list.
void add(WordList list, char *str, int size);

// delete()
// Deletes string from position index.
// Pre: 1 <= index <= size(list)
void delete(WordList list, int index);

// deleteAll()
// Reset list to the empty state.
void deleteAll(WordList list);


// Other Operations -----------------------------------------------------------


void printWordList(char *fileName, FILE **out, WordList list);

void wordListSort(WordList list);

#endif
