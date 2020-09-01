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
void freeWordList(WordList* pL);


// ADT operations -------------------------------------------------------------


// isEmpty()
// Returns 1 (true) if WordList L is empty, 0 (false) otherwise.
int isEmpty(WordList L);

// size()
// Returns the number of elements in L.
int size(WordList L);

// add()
// Inserts string s into L.
void add(WordList L, char *str, int size);

// delete()
// Deletes string from position index.
// Pre: 1 <= index <= size(L)
void delete(WordList L, int index);

// deleteAll()
// Reset L to the empty state.
void deleteAll(WordList L);


// Other Operations -----------------------------------------------------------


void printWordList(WordList L);

void wordListSort(WordList L);

#endif
