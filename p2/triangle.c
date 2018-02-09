/** A program that draws a triangle given a width and height value
  * for the image, 3 (x, y) coordinate pairs for the vertices,
  * and 3 integers for the RGB values corresponding to the desired
  * color of the triangle. The program outputs a ppm file that is
  * either encoded using 8 bit ints or binary representation.
  * @file triangle.c
  * @author Noah Benveniste nnbenven
  */
#include <stdlib.h>
#include <stdio.h>
#include "geometry.h"
#include "encoding.h"

/** Main function; starting point for the program. Validates
  * user input, passes it to functions that handle drawing.
  * @param NONE
  * @return int 0 for successful run, anything else for failure
  */
int main()
{
    
    // Image dimensions must be positive integers
    int imageWidth, imageHeight;
    int imageWidthValid = scanf( "%d", &imageWidth );
    int imageHeightValid = scanf( "%d", &imageHeight );
    if ( imageWidthValid != 1 || imageHeightValid != 1 ) {
        return EXIT_FAILURE;
    } else if ( imageWidth <= 0 || imageHeight <= 0 ) {
        return EXIT_FAILURE;
    }
    
    // Triangle vertices must all be doubles
    double x1, y1, x2, y2, x3, y3;
    int x1Valid = scanf( "%lf", &x1 );
    int y1Valid = scanf( "%lf", &y1 );
    int x2Valid = scanf( "%lf", &x2 );
    int y2Valid = scanf( "%lf", &y2 );
    int x3Valid = scanf( "%lf", &x3 );
    int y3Valid = scanf( "%lf", &y3 );
    if ( x1Valid != 1 || y1Valid != 1 || x2Valid != 1 || y2Valid != 1 || x3Valid != 1 || y3Valid != 1 ) {
        return EXIT_FAILURE;
    }
    
    // RGB values must be integers from 0 to 255 inclusive
    int rVal, gVal, bVal;
    int rValValid = scanf( "%d", &rVal );
    int gValValid = scanf( "%d", &gVal );
    int bValValid = scanf( "%d", &bVal );
    if ( rValValid != 1 || gValValid != 1 || bValValid != 1 ) {
        return EXIT_FAILURE;
    } else if ( rVal < 0 || rVal > 255 || gVal < 0 || gVal > 255 || bVal < 0 || bVal > 255 ) {
        return EXIT_FAILURE;
    }
    
    printHeader( imageWidth, imageHeight );
    for ( int i = 0; i < imageHeight; i++ ) {
        for ( int j = 0; j < imageWidth; j++ ) {
            double currPixelCenterX = j + 0.5;
            double currPixelCenterY = i + 0.5;
            if ( inside(x1, y1, x2, y2, x3, y3, currPixelCenterX, currPixelCenterY ) ) {
                // Print the pixel with the given RGB value
                printValue( rVal );
                printValue( gVal );
                printValue( bVal );
            } else {
                // Print the pixel black
                printValue( 0 );
                printValue( 0 );
                printValue( 0 );
            }
        }
    }
    // End with a new line
    printf( "\n" );
    
    return EXIT_SUCCESS;
    
}