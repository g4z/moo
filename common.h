/*
 * Copyright (c) 2002 Mayukh Bose
 * See the file LICENSE for details.
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>
using namespace std;

#define LASTKEYWORD "endofkeyword"
typedef enum {ttNone = 0, ttEOF, ttIdentifier, ttKeyword, ttSymbol, ttNumber, ttString} TagTypes;
// FIXME - Add the keywords later.
extern string Keywords[];
extern string Symbols;

// Ordinals of the various commands in the Keywords[] array
#define PRINT_CMD 0
#define IF_CMD 1
#define THEN_CMD 2
#define ELSE_CMD 3
#define BEGIN_CMD 4
#define END_CMD 5
#define WHILE_CMD 7
#define DO_CMD    8
#define INPUT_CMD 9

#endif

