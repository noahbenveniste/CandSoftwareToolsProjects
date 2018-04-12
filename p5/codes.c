/**
 * Functions invloved generating a dictionary of symbols and binary codes
 * and functionality to search for a given symbol or code given a symbol or code.
 *
 * @file codes.c
 * @author Noah Benveniste
 */
#include "codes.h"

/* A statically allocated array to serve as the code dictionary */
CodeDictEntry codeDict[CODE_DICT_SIZE];
/* Keeps track of the number of entries added to the dictionary so far */
int numEntries;

CodeDictEntry parseEntry( FILE * fp )
{
    // A code file is invalid if:
    // 1. a symbol name is not legal (i.e. isn't a-z, "space", "newline", or "eof"
    // 2. a symbol is listed multiple times
    // 3. an encoding string isn't a series of up to 12 0s and 1s
    // 4. the number of symbols is not equal to 29

    /* Print "Invalid code file" to stderr and exit with a status of 1 */
    // Initialize symbol and code
    char sym[CODE_DICT_SIZE];
    char code[CODE_DICT_SIZE];
    char symbol;
    CodeDictEntry entry;

    // Read in the line of input
    int matches = fscanf( fp, "%s %s", sym, code );

    // Check for EOF
    if ( matches == EOF ) {
        strcpy( entry.bits, "ENDFILE" );
        return entry;
    }

    if ( matches != 2 ) {
        fprintf( stderr, "Invalid code file" );
        fclose( fp );
        exit( EXIT_FAILURE );
    }

    // Check that the symbol is valid (see above)
    if ( strlen( sym ) == 1 ) {
        if ( sym[0] < 'a' || sym[0] > 'z' ) {
            fprintf( stderr, "Invalid code file" );
            fclose( fp );
            exit( EXIT_FAILURE );
        } else {
            symbol = sym[0];
        }
    } else {
        if ( strcmp( "space", sym ) == 0 ) {
            symbol = ' ';
        } else if ( strcmp( "newline", sym ) == 0 ) {
            symbol = '\n';
        } else if ( strcmp( "eof", sym ) == 0 ) {
            symbol = EOF;
        } else {
            fprintf( stderr, "Invalid code file" );
            fclose( fp );
            exit( EXIT_FAILURE );
        }
    }

    // Check that the dictionary doesn't already contain the symbol
    for ( int i = 0; i < numEntries; i++ ) {
        if ( codeDict[i].ch == symbol ) {
            fprintf( stderr, "Invalid code file" );
            fclose( fp );
            exit( EXIT_FAILURE );
        }
    }

    // Check that the code string is a series of 1's and 0's and is at most 12 characters
    if ( strlen( code ) > BIT_STR_LEN ) {
        fprintf( stderr, "Invalid code file" );
        fclose( fp );
        exit( EXIT_FAILURE );
    }

    for ( int i = 0; i < strlen( code ); i++ ) {
        if ( code[i] != '1' && code[i] != '0' ) {
            fprintf( stderr, "Invalid code file" );
            fclose( fp );
            exit( EXIT_FAILURE );
        }
    }

    // If this point is reached, the inputs are valid, so construct a dictionary entry and add them to the array
    entry.ch = symbol;
    strcpy( entry.bits, code );

    return entry;
}

const char * symToCode( int ch )
{
    for ( int i = 0; i < numEntries; i++ ) {
        if ( ch == codeDict[i].ch ) {
            return codeDict[i].bits;
        }
    }

    // The case that the symbol isn't found
    return NULL;
}

int codeToSym( const char *code )
{
    for ( int i = 0; i < numEntries; i++ ) {
        if ( strcmp( code, codeDict[i].bits ) == 0 ) {
            return codeDict[i].ch;
        }
    }

    // The case that the code wasn't found
    return -2;
}

/* Used for debugging */
void displayEntry( CodeDictEntry e ) {
    printf( "%c, %s\n", e.ch, e.bits );
}

/* Used for debugging
int main()
{
    // Read in the input file
    FILE *fp;

    fp = fopen( "codes-1.txt", "r" );

    if ( !fp ) {
        fprintf( stderr, "No such file or directory" );
        exit( EXIT_FAILURE );
    }

    numEntries = 0;

    CodeDictEntry entry = parseEntry( fp );
    while ( strcmp( entry.bits, "ENDFILE" ) != 0 ) {

        codeDict[numEntries] = entry;
        numEntries++;

        entry = parseEntry( fp );
    }

    // Check if the code dictionary is the correct length
    if ( numEntries != 29 ) {
        fprintf( stderr, "Invalid code file" );
        fclose( fp );
        exit( EXIT_FAILURE );
    }

    fclose( fp );

    for ( int i = 0; i < numEntries; i++ ) {
        displayEntry( codeDict[i] );
    }

    // Testing symToCode
    printf( "\nTesting symToCode\n" );
    printf( "Expected: 11010000111\n" );
    printf( "Actual  : %s\n", symToCode( EOF ) );

    // Testing codeToSym
    printf( "\nTesting codeToSym\n" );
    bool eofFound = ( codeToSym( "11010000111" ) == EOF );
    if ( eofFound ) {
        printf( "EOF successfully found\n" );
    } else {
        printf( "EOF not found\n" );
    }

    return 0;
}
*/