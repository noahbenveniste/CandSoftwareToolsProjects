#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "wordlist.h"

int main( int argc, char *argv[] )
{
	// Store the RNG seed if one is provided
	int seed;
	// RNG index for word to be chosen each game
	int index;
	
	// Check for correct number of command line arguments
	if ( argc < 2 || argc > 3 ) {
		goto commandLineArgError;
	}
	
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
		// Generate the index of the word to be chosen
		index = rand() % wordCount;
		
		// Get the word to be used for this round
		char *actualWord = words[ index ];
		
		// Initialize the string containing the underscores
		char wordToDisplay[ strlen( actualWord ) + 1 ];
		for ( int i = 0; i < strlen( actualWord ); i++ ) {
			wordToDisplay[ i ] = '_';
		}
		wordToDisplay[ strlen( actualWord ) ] = '\0';
		
		// Initialize array containing alphabet
		char letters[] = "abcdefghijklmnopqrstuvwxyz";
		
		// Initialize wrong guesses counter
		int numWrongGuesses = 0;
		
		// The number of letters the player must guess to win
		int numLettersToGuess = strlen( actualWord );
		
		// Flag to tell if the player has won
		bool playerHasWon = false;
		
		// Keep prompting user for guesses
		while ( numWrongGuesses < 7 ) {
			// Print the figure based on the number of wrong guesses
			
			// Print the display word
			
			// Print the remaining letters to guess
			
			// Check for garbage input. User must enter a lowercase letter.
			
			// Reprompt if user inputs garbage
			
			// For a valid input, check the actual word array. Loop through each
			// element in the array. If a given index contains the guessed letter,
			// go to the display word array and swap out the underscore with the
			// letter at that index and increment the correct guess counter.
			// Set a boolean flag so that the wrong guesses counter doesn't increment. 
			// Remove the guessed letter from the letters array. Increment the 
			// guessed letter counter. If the player has guessed all the letters, set
			// win flag and break
			
			// If the guessed letter was not found in the word, the boolean flag won't be
			// set so increment the wrong guesses counter.
		}
		// Check if the player has won or lost and output proper message
		
		// Ask the user if they want to play again. y or Y indicates yes, anything else or EOF means no
		playAgain = false;
	}
	
	return EXIT_SUCCESS;
	
	// Error handling for command line arguments
	commandLineArgError:
		fprintf( stderr, "usage: hangman <word-file> [seed]\n" );
		return EXIT_FAILURE;
}