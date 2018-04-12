/**
 * Prototypes for functions invloved generating a dictionary of symbols and binary codes
 * and functionality to search for a given symbol or code given a symbol or code.
 *
 * @file codes.h
 * @author Noah Benveniste
 */
#ifndef _CODES_H_
#define _CODES_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/** Size of the code dictionary buffer array */
#define CODE_DICT_SIZE 50
/** Max length of a bit string code */
#define BIT_STR_LEN 12

/** An entry in the code dictionary; stores the character and associated binary code */
typedef struct {

    /** The actual character to be encoded */
    char ch;

    /** The bit string for the encoded character */
    char bits[BIT_STR_LEN + 1];

} CodeDictEntry;

/** The code dictionary; made to be accessible to the 
    whole program so it can be statically allocated */
extern CodeDictEntry codeDict[CODE_DICT_SIZE];
/** The number of entries currently in the code dictionary*/
extern int numEntries;

/**
 * Generates a dicionary entry given a line from an input codes file
 *
 * @return a CodeDictEntry struct representing the line parsed from the file
 */
CodeDictEntry parseEntry( FILE * fp );

/**
 *
 */
const char * symToCode( int ch );

/**
 *
 */
int codeToSym( const char *code );

#endif
