#include "codes.h"

void initCodeDictionary( char * fileName )
{
    // A code file is invalid if:
    // 1. a symbol name is not legal (i.e. isn't a-z, "space", "newline", or "eof"
    // 2. a symbol is listed multiple times
    // 3. an encoding string isn't a series of up to 12 0s and 1s
    // 4. the number of symbols is not equal to 29
    
    /* Print "Invalid code file" to stderr and exit with a status of 1 */
}

const char * symToCode( int ch )
{
    
}

int codeToSym( const char *code )
{
    
}