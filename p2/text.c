/** Encodes ppm file that produces triangle image using
  * 8 bit integers.
  * @file text.c
  * @author Noah Benveniste
  */
#include "encoding.h"

/** Max number of characters to print on a line */
#define MAX_LINE_LENGTH 70

void printHeader( int width, int height )
{
    printf( "P3\n%d %d\n%d\n", width, height, CMAX );
}

void printValue( unsigned char c )
{
    
    // Keep track of the number of characters on the current line
    static int charCount = 0;
    /* 
      If the lenth of the integer preceded by a space plus 
      the current number of characters exceeds 70, go down
      a line and don't print a space.
    */
    
    // Cast to an int
    int currInt = (int) c;
    // The width of the int plus a space to be added to the line
    int width;
    // Determine the length of the passed integer
    if ( currInt >= 100 ) {
        width = 4;
    } else if ( currInt >= 10 ) {
        width = 3;
    } else {
        width = 2;
    }
    
    // When charCount = 0, on the first line. Print the int with no space
    if ( charCount == 0 ) {
        printf( "%d", currInt );
        charCount = charCount + width;
    // If adding the current int with a space won't exceed the max line length, print on this line
    } else if ( width + charCount <= MAX_LINE_LENGTH ) {
        printf( " %d", currInt );
        charCount = charCount + width;
    // If it would exceed, go down a line and print, reset static counter
    } else {
        printf( "\n%d", currInt );
        charCount = width - 1;
    }
    
}