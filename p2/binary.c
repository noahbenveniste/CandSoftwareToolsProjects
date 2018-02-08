#include "encoding.h"

void printHeader( int width, int height )
{
    printf( "P6\n%d %d\n%d\n", width, height, CMAX );
}

void printValue( unsigned char c )
{
    putchar( c );
}