//-----------------------------------------------------------------------------
// wordlist.c
// Linked List implementation of the WordList ADT.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"wordlist.h"


// Private Types and Functions ------------------------------------------------

// NodeObj
typedef struct NodeObj{
   char* word;
   int count;
   struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// Constructor for private Node type.
Node newNode(char* s, int size) {
   Node N = malloc(sizeof(NodeObj));
   N->word = calloc(size+1, sizeof(char));
   strncpy(N->word, s, size);
   N->word[size] = '\0';
   N->count = 1;
   N->next = NULL;
   return N;
}

// freeNode()
// Destructor for private Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// WordListObj
typedef struct WordListObj{
   Node head;
   int numWords;
} WordListObj;

// find()
// Returns a reference to the Node with string str in L.
Node find(WordList L, char *str){
	if (L == NULL) {
		fprintf(stderr, "WordList Error: calling find() on NULL WordList reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = L->head;
	while (N != NULL) {
		if (strcmp(N->word, str) == 0) {
			return N;
		}
		N = N->next;
	}
	return N;
}

// countChars()
// Returns the number of characters in a text representation of L. Used by
// WordListToString() to allocate sufficient heap memory.  Does not count
// the terminating null '\0' character.
int countChars(WordList L){
   int count = 0;
   Node N = L->head;
   while( N!=NULL ){
      count += strlen(N->word) + 1; // all all the string lengths and the
                                    // spaces in between
      N = N->next;
   }
   if( (L->numWords)>0 ){
      count -= 1;                   // no space after the last string
   }
   return count;   
}


// Constructors-Destructors ---------------------------------------------------

// newWordList()
// Constructor for the WordList type.
WordList newWordList(){
   WordList L = malloc(sizeof(WordListObj));
   L->head = NULL;
   L->numWords = 0;
   return L;
}

// freeWordList()
// Destructor for the WordList type.
void freeWordList(WordList* pL){
   if( pL!=NULL && *pL!=NULL ){
      deleteAll(*pL);
      free(*pL);
      *pL = NULL;
   }
}


// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if WordList L is empty, 0 (false) otherwise.
int isEmpty(WordList L){
   if( L==NULL ){
      fprintf(stderr, 
         "WordList Error: calling isEmpty() on NULL WordList reference\n");
      exit(EXIT_FAILURE);
   }
   return (L->numWords==0) ;
}

// size()
// Returns the number of elements in L.
int size(WordList L){
   if( L==NULL ){
      fprintf(stderr, 
         "WordList Error: calling size() on NULL WordList reference\n");
      exit(EXIT_FAILURE);
   }
   return L->numWords;
}

// check()
// Checks if string str is in L.
Node check(WordList L, char *str){
	Node N = find(L, str);
	return N;
}

// duplicate()
// Increments the count field in Node N.
void duplicate(WordList L, Node N){
	if (L == NULL) {
   		fprintf(stderr, "WordList Error: calling get() on NULL WordList reference\n");
		exit(EXIT_FAILURE);
	}
	N->count++;
	return;
}

// add()
// Inserts string s into L.
void add(WordList L, char* str, int size){
	Node N = NULL;
	if (L == NULL) {
		fprintf(stderr, "WordList Error: calling add() on NULL WordList reference\n");
		exit(EXIT_FAILURE);
	}
	N = check(L, str);

	if (N != NULL) {
		duplicate(L, N);
		return;
	}
	N = newNode(str, size);
	N->next = L->head;
	L->head = N;
	(L->numWords)++;
	return;
}

// deleteAll()
// Reset L to the empty state.
void deleteAll(WordList L){
   Node N=NULL;
   if( L==NULL ){
      fprintf(stderr, 
         "WordList Error: calling deleteAll() on NULL WordList reference\n");
      exit(EXIT_FAILURE);
   }

   while( L->numWords > 0 ){
      N = L->head;
      L->head = L->head->next;
      N->next = NULL;
      freeNode(&N);
      L->numWords--;
   }
}


// Other Operations -----------------------------------------------------------


void printWordList(WordList L) {
	Node N;
	if (L == NULL) {
		fprintf(stderr, "WordList Error: calling printWordList() on NULL WordList reference\n");
		exit(EXIT_FAILURE);
	}
	N = L->head;
	while (N != NULL) {
      printf("%s", N->word);
	  printf(" ");
	  printf("%d", N->count);
      printf("\n");
      N = N->next;
   }
}

Node SortedMerge(Node a, Node b) { 
    Node result = NULL; 
  
    /* Base cases */
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 
  
    /* Pick either a or b, and recur */
    if (strcmp(a->word, b->word) <= 0) { 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 
    return (result); 
} 

void FrontBackSplit(Node source, Node* frontRef, Node* backRef) { 
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
  
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 

void MergeSort(Node* headRef) { 
    Node head = *headRef; 
    Node a; 
    Node b; 
  
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
  
    // Split the list into two sublists
    FrontBackSplit(head, &a, &b); 
  
    // Recursively sort the sublists
    MergeSort(&a); 
    MergeSort(&b); 
  
    // Merge the two sorted lists together
    *headRef = SortedMerge(a, b); 
} 

void WordListSort(WordList L) { 
	MergeSort(&(L->head));
	return; 
}