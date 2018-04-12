/**
 * Handles functionality for encoding a given input file given a code
 * conversion dictionary and then outputting the encoded file to a specified
 * path.
 *
 * @file encode.c
 * @author Noah Benveniste
 */
#include "bits.h"
#include "codes.h"

/** The number of command line arguments needed by the program */
#define NUM_ARGS 3
/** Max number of entries in the code dict */
#define DICT_LEN 29

/**
 * Main method; handles primary flow of control of encode functionality
 */
int main( int argc, char *argv[] )
{
    // Check that the correct number of command line args were provided
    if ( argc != NUM_ARGS + 1 ) {
        fprintf( stderr, "usage: encode <codes-file> <infile> <outfile>\n" );
        exit( EXIT_FAILURE );
    }

    // Try to open the provided files
    FILE *fpcodes = fopen( argv[1], "r" );
    FILE *fpin = fopen( argv[2], "r" );
    FILE *fpout = fopen( argv[3], "wb" );

    if ( !fpcodes ) {
        fprintf( stderr, "%s: No such file or directory\n", argv[1] );
        exit( EXIT_FAILURE );
    } else if ( !fpin ) {
        fprintf( stderr, "%s: No such file or directory\n", argv[2] );
        exit( EXIT_FAILURE );
    } else if ( !fpout ) {
        fprintf( stderr, "%s: No such file or directory\n", argv[3] );
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

    int nxtChar;
    do {
        // Read in the input file. If it contains symbols not found in the dictionary, print "Invalid input file"
        nxtChar = fgetc( fpin );
        /*
        if ( nxtChar == EOF ) {
            printf ("EOF\n" );
        } else {
            printf ( "%c\n", nxtChar );
        }
        */

        // Look up the character in the dictionary. If NULL is returned, print "Invalid input file", close all files, exit 1
        const char *bitString = symToCode( nxtChar );
        //printf( "%s\n", bitString );

        // Symbol wasn't found
        if ( !bitString ) {
            fprintf( stderr, "Invalid input file\n" );
            fclose( fpcodes );
            fclose( fpin );
            fclose( fpout );
            exit( EXIT_FAILURE );
        }

        // Symbol was found, write the bits to the encoded file
        writeBits( bitString, &buffer, fpout );
        //printf( "%d\n", buffer.bcount );

    } while ( nxtChar != EOF );

    // Once EOF is reached, need to flush any remaining bits

    //printf( "Number of bits left in buffer: %d\n", buffer.bcount );
    //printf( "Byte left in buffer: %c\n", buffer.bits );
    flushBits( &buffer, fpout );

    fclose( fpcodes );
    fclose( fpin );
    fclose( fpout );
    return 0;
}