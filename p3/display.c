/**
  * @file
  * @author
  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "display.h"

void displayWord(char word[])
{
    printf( "%c", word[ 0 ] );
    for ( int i = 1; i < strlen( word ); i++ ) {
        printf( " %c", word[ i ] );
    }
    printf( "\n" );
    return;
}

void displayFigure(int numberOfParts)
{
    char *bodyParts[] = {
                "\n O \n",
                "\n O \n | \n",
                "\n O \n | \n | \n",
                "\n O \n/| \n | \n",
                "\n O \n/|\\\n | \n",
                "\n O \n/|\\\n | \n/\n",
                "\n O \n/|\\\n | \n/ \\\n",
                };
    if ( numberOfParts > 0 ) {
        printf( "%s", bodyParts[ numberOfParts - 1] );
    }
    return;
}
