//-----------------------------------------------------------------------------
// vstring.h
//
// Implements a variable string into which characters can be accumulated, using
// array doubling when the length of the string is exceeded.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#ifndef _VSTRING_H_
#define _VSTRING_H_

int vstring(char ch, char **buffer, int index, int *size);

#endif