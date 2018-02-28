#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "wordlist.h"

int main( int argc, char *argv[] )
{
	// Store the RNG seed if one is provided
	int seed;
	// RNG index for word to be chosen each game
	int index;
	
	// Seed provided
	if ( argc == 3 ) {
		seed = atoi( argv[2] );
		if ( seed > 0 ) {
			srand( seed );
		} else {
			goto commandLineArgError;
		}
	} else {
		srand( time( NULL ) ); // No seed provided
	}
	
	// Load the list of words
	readWords( argv[1] );
	
	// Loop for file i/o debugging
	for ( int i = 0; i < wordCount; i++ ) {
		printf( "%s\n", words[ i ] );
	}
	printf( "%d\n", wordCount );
	
	// Repeat game loop
	bool playAgain = true;
	while ( playAgain ) {
		index = rand() % wordCount;
		playAgain = false;
	}
	
	return EXIT_SUCCESS;
	
	commandLineArgError:
		fprintf( stderr, "usage: hangman <word-file> [seed]\n" );
		return EXIT_FAILURE;
}