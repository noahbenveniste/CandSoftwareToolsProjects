#ifndef _CODES_H_
#def _CODES_H_

#include <stdio.h>
#include <stdlib.h>

#define CODE_DICT_SIZE 50

/** An entry in the code dictionary; stores the character and associated binary code */
typedef struct {
    
    /** The actual character to be encoded */
    char ch;
    
    /** The bit string for the encoded character */
    char *bits;
    
} CodeDictEntry;

/** */
extern CodeDictEntry codeDict[CODE_DICT_SIZE];

/**
 *
 */
void initCodeDict( char * fileName );

/**
 *
 */
const char * symToCode( int ch );

/**
 *
 */
int codeToSym( const char *code );

#endif