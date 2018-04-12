/**
 * File containing methods that handle the buffering of bits when doing
 * binary i/o with whole bytes of data.
 *
 * @file bits.c
 * @author Noah Benveniste
 */
#include <stdlib.h>
#include <string.h>
#include "bits.h"

void writeBits( const char *code, BitBuffer *buffer, FILE *fp )
{
    // Add bits to the BitBuffer one at a time, left shifting each time
    // until 8 bits are stored. Write the 8 bits. Then, add any leftover
    // bits.

    // Loop through the input bit string until the BitBuffer hits 8 bits or null terminator is hit
    int idx = 0;
    char ch = code[idx];

    while ( ch != '\0' ) {
        while ( buffer->bcount < 8 ) {

            // Grab the next character from the bit string, append it to the end of the BitBuffer.
            // Then, left shift the bit that was just added by 7 - buffer->bcount
            int nxtBit = ch - '0';

            // Convert to octal
            if ( nxtBit == 0 ) {
                nxtBit = 0x0;
            } else if ( nxtBit == 1 ) {
                nxtBit = 0x1;
            } else {
                return;
            }

            // Create a mask by left shifting the inserted bit
            int mask = nxtBit << ( 7 - buffer->bcount );

            // Or the mask onto the buffer's bits
            buffer->bits |= mask;

            // Increment bcount++
            buffer->bcount++;

            // Get the next bit from the bit string
            idx++;
            ch = code[idx];
        }

        // Check if null terminator was reached i.e. the buffer didn't fill. If it didnt, return.
        if ( buffer->bcount < 8 ) {
            return;
        }

        // Once buffer->bcount hits 8, write the byte and reset the buffer's bit count
        fprintf( fp, "%c", buffer->bits );
        buffer->bcount = 0;
        buffer->bits = 0x0;
    }
    /*
    // Check if code has any more characters to write. Write the rest of these to the buffer
    // in the same way that was done above until the null terminator is reached.
    while ( ch != '\0' ) {
        // Grab the next character from the bit string, append it to the end of the BitBuffer.
        // Then, left shift the bit that was just added by 7 - buffer->bcount
        int nxtBit = ch - '0';

        // Convert to octal
        if ( nxtBit == 0 ) {
            nxtBit = 0x0;
        } else if ( nxtBit == 1 ) {
            nxtBit = 0x1;
        } else {
            printf( "Invalid bit string" );
            return;
        }

        // Create a mask by left shifting the inserted bit
        int mask = nxtBit << ( 7 - buffer->bcount );

        // Or the mask onto the buffer's bits
        buffer->bits |= mask;

        // Increment bcount++
        buffer->bcount++;

        // Get the next bit from the bit string
        idx++;
        ch = code[idx];
    }
    */
    return;
}

/* Used when encoding the input file when EOF is reached to flush the last byte from the bit buffer */
void flushBits( BitBuffer *buffer, FILE *fp )
{
    if ( buffer->bcount != 0 ) {
        fprintf( fp, "%c", buffer->bits );
        buffer->bits = 0x0;
        buffer->bcount = 0;
    }
    return;
}

int readBit( BitBuffer *buffer, FILE *fp )
{
    // If the buffer is empty, read in the next byte from the file and put it in the buffer
    if ( buffer->bcount == 0 ) {
        int temp = fgetc( fp );
        if ( temp == EOF ) {
            return -1;
        } else {
            buffer->bits = temp;
            buffer->bcount = 8;
        }
    }

    // Regardless of the above condition, grab the highest-order bit from the buffer, left-shift
    // the remaining bits, decrement bcount, and return the bit
    int nxtBit = buffer->bits & ( 1 << 7 );
    int outBit;
    if ( nxtBit == 0x0 ) {
        outBit = 0;
    } else {
        outBit = 1;
    }

    int temp = buffer->bits;
    temp = temp << 1;
    buffer->bits = temp;

    buffer->bcount--;
    return outBit;
}

/* Used for testing bit reading and writing functionality
int main()
{
    // Initialize the bit buffer
    BitBuffer buffer;
    buffer.bcount = 0;
    buffer.bits = 0x0;

    FILE *fp;
    fp = fopen( "encoded-1.bin", "rb" );

    if ( !fp ) {
        printf( "Unable to open input encoded file\n" );
        return 1;
    } else {
        printf( "Successfully opened input encoded file\n" );
    }

    int nxtBit = readBit( &buffer, fp );
    while ( nxtBit != -1 ) {
        printf( "%d", nxtBit );
        nxtBit = readBit( &buffer, fp );
    }
    printf( "\n" );

    buffer.bcount = 0;
    buffer.bits = 0x0;

    char *byte1 = "00100110";
    char *byte2 = "11110100";
    char *byte3 = "00110110";
    char *byte4 = "10000111";

    fp = fopen( "test-encode-1.bin", "wb" );
    writeBits( byte1, &buffer, fp );
    writeBits( byte2, &buffer, fp );
    writeBits( byte3, &buffer, fp );
    writeBits( byte4, &buffer, fp );
    flushBits( &buffer, fp );

    fclose( fp );

    char *expected = "00100110111101000011011010000111\n";

    FILE *fpin = fopen( "test-encode-1.bin", "rb" );

    buffer.bcount = 0;
    buffer.bits = 0x0;

    nxtBit = readBit( &buffer, fpin );
    printf( "First bit read from encoded file: %d\n", nxtBit );

    printf( "actual   = " );
    while ( nxtBit != -1 ) {
        printf( "%d", nxtBit );
        nxtBit = readBit( &buffer, fpin );
    }
    printf( "\n" );

    printf( "expected = %s", expected );

    fclose( fpin );
    return 0;
}
*/