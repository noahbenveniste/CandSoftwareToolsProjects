/**
 * Handles functionality for decoding a given input file given a code
 * conversion dictionary and then outputting the decoded file to a specified
 * path.
 *
 * @file decode.c
 * @author Noah Benveniste
 */
#include "bits.h"
#include "codes.h"

/** The number of arguments needed by the program */
#define NUM_ARGS 3
/** Max number of entries in the code dict */
#define DICT_LEN 29

/**
 * Main method; handles primary flow of control of decode functionality
 */
int main( int argc, char *argv[] )
{
    // Check that the correct number of command line args were provided
    if ( argc != NUM_ARGS + 1 ) {
        fprintf( stderr, "usage: decode <codes-file> <infile> <outfile>\n" );
        exit( EXIT_FAILURE );
    }

    // Try to open the provided files
    FILE *fpcodes = fopen( argv[1], "r" );
    FILE *fpin = fopen( argv[NUM_ARGS - 1], "rb" );
    FILE *fpout = fopen( argv[NUM_ARGS], "w" );

    if ( !fpcodes ) {
        fprintf( stderr, "%s: No such file or directory\n", argv[1] );
        exit( EXIT_FAILURE );
    } else if ( !fpin ) {
        fprintf( stderr, "%s: No such file or directory\n", argv[NUM_ARGS - 1] );
        exit( EXIT_FAILURE );
    } else if ( !fpout ) {
        fprintf( stderr, "%s: No such file or directory\n", argv[NUM_ARGS] );
        exit( EXIT_FAILURE );
    }

    // Build the code dictionary
    numEntries = 0;

    CodeDictEntry entry = parseEntry( fpcodes );
    while ( strcmp( entry.bits, "ENDFILE" ) != 0 ) {

        codeDict[numEntries] = entry;
        numEntries++;

        entry = parseEntry( fpcodes );
    }

    // Check if the code dictionary is the correct length
    if ( numEntries != DICT_LEN ) {
        fprintf( stderr, "Invalid code file\n" );
        fclose( fpcodes );
        fclose( fpin );
        fclose( fpout );
        exit( EXIT_FAILURE );
    }

    // Initialize the bit buffer
    BitBuffer buffer;
    buffer.bcount = 0;
    buffer.bits = 0x0;

    // Fencepost
    int bit = readBit( &buffer, fpin );
    char bitStringBuffer[BIT_STR_LEN + 1];
    while ( bit != -1 ) {
        // Concatenate the bit onto a bit string. Try to find a
        // symbol that matches in the dictionary.
        char currentBit[2];
        sprintf( currentBit, "%d", bit );
        //printf( "Current bit: %s\n", currentBit );
        strcat( bitStringBuffer, currentBit );
        //printf( "Bit string: %s\n\n", bitStringBuffer );

        // If codeToSym returns anything other than EOF, write the
        // symbol to the file. Then, reset the bit string buffer
        int sym = codeToSym( bitStringBuffer );

        if ( sym != -2 && sym != EOF ) {
            fputc( sym, fpout );
            strcpy( bitStringBuffer, "" ); // Empties the bit string
        } else if ( sym == EOF ) {
            break;
        } else {
            if ( strlen( bitStringBuffer ) == BIT_STR_LEN ) {
                strcpy( bitStringBuffer, "" ); // Empties the bit string
            }
        }

        // Get the next bit
        bit = readBit( &buffer, fpin );
    }

    fclose( fpcodes );
    fclose( fpin );
    fclose( fpout );
    return 0;
}
