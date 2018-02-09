/** Functions necessary for generating output ppm files.
  * Can be used for either 8 bit integer or binary
  * encoding.
  * @file encoding.h
  * @author Noah Benveniste
  */
#include <stdlib.h>
#include <stdio.h>

/** Maximum color component value. */
#define CMAX 255

/** Prints the header of the ppm file, given
  * the width and height of the image in pixels
  * @param width the width of the image in pixels
  * @param height the heiight of the image in pixels
  */
void printHeader( int width, int height );

/** Prints an RGB component value to the output destination.
  * @param c the RGB component to be printed
  */
void printValue( unsigned char c );
