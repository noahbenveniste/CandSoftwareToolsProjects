#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordlist.h"

/** Statically allocated words array. Can store 50 words with 20 characters each (plus null terminator) */
char words[50][21];
int wordCount;

void readWords( char const *filename )
{
	// Try to open a file with the specified name
	FILE *f = fopen( filename, "r" );
	if (!f) {
		fprintf( stderr, "Can't open word file\n");
		exit( EXIT_FAILURE );
	}
	
	// Stores each word in the file. Used to check if the word is over 20 characters.
	char buffer[100];
	// Initialize the word counter
	wordCount = 0;
	// Fencepost for loop control
	char curr = fgetc( f );
	
	// Loop until EOF is reached
	while ( curr != EOF ) {
		// Put the character back
		ungetc( curr, f );
		// If another loop iteration is reached with 50 words in the array, the file has too many words.
		if ( wordCount == 50 ) {
			goto invalidWordFile;
		}
		// Scan in a word
		int matches = fscanf( f, "%s", buffer );
		// Check that the word doesn't have more than 20 characters
		int currentWordLength = strlen( buffer );
		if ( currentWordLength > 20 ) {
			goto invalidWordFile;
		}
		// Check that the word doesn't contain anything other than lower case letters
		for ( int i = 0; i < currentWordLength; i++ ) {
			if ( buffer[i] < 'a' || buffer[i] > 'z' ) {
				goto invalidWordFile;
			}
		}
		// Check if EOF has been reached
		if ( matches == EOF ) {
			break;
		}
		// If the word was valid, add the word to the words array and increment the word count
		strcpy( words[ wordCount ], buffer );
		// Get a character to check for EOF
		curr = fgetc( f );
		// Increment word counter
		wordCount++;
	}
	fclose( f );
	return;
	
	invalidWordFile:
		fprintf( stderr, "Invalid word file\n" );
		fclose( f );
		exit( EXIT_FAILURE );
		
}