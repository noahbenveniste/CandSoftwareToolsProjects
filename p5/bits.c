#include "bits.h"

void writeBits( const char *code, BitBuffer *buffer, FILE *fp )
{
    // Add bits to the BitBuffer one at a time, left shifting each time
    // until 8 bits are stored. Write the 8 bits. Then, add any leftover
    // bits.
    
    // Loop through the input bit string until the BitBuffer hits 8 bits or null terminator is hit
    
    // Grab the next character from the bit string, append it to the end of the BitBuffer.
    // Then, left shift the bit that was just added by 7 - buffer->bcount
    
    // Once buffer->bcount hits 8, write the byte and reset buffer->bits
    
    // Check if code has any more characters to write. Write the rest of these to the buffer
    // in the same way that was done above until the null terminator is reached.
}

void flushBits( BitBuffer *buffer, FILE *fp )
{
    // Check buffer->bcount. Write that number of bits, taking from the highest order bits in the buffer,
    // then print 0s for the remaining 8 - bcount bits 
}

int readBit( BitBuffer *buffer, FILE *fp )
{
    // If the buffer is empty, read in the next byte from the file and put it in the buffer
    
    // Regardless of the above condition, grab the highest-order bit from the buffer, left-shift
    // the remaining bits, decrement bcount, and return the bit
    
    // If EOF is read, return -1
}