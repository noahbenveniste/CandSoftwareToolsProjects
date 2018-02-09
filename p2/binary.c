/** Encodes file containing triangle image using a more
  * compressed binary representation.
  * @file binary.c
  * @author Noah Benveniste
  */
#include "encoding.h"

void printHeader( int width, int height )
{
    printf( "P6\n%d %d\n%d\n", width, height, CMAX );
}

void printValue( unsigned char c )
{
    // Prints the integer's ascii value
    putchar( c );
}