/**
  * @file
  * @author
  */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "wordlist.h"
#include "display.h"

#define MIN_ARGS 2
#define MAX_ARGS 3
#define NUM_GUESSES 7

int main( int argc, char *argv[] )
{
    // Store the RNG seed if one is provided
    int seed;
    // RNG index for word to be chosen each game
    int index;

    // Check for correct number of command line arguments
    if ( argc < MIN_ARGS || argc > MAX_ARGS ) {
        goto commandLineArgError;
    }

    // Seed provided
    if ( argc == MAX_ARGS ) {
        seed = atoi( argv[MAX_ARGS - 1] );
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

        // Initialize correct guesses counter
        int numLettersGuessed = 0;

        // The number of letters the player must guess to win
        int numLettersToGuess = strlen( actualWord );

        // Flag to tell if the player has won
        bool playerHasWon = false;

        // Keep prompting user for guesses
        do {
            // Flag for correct letter guess
            bool correctGuess = false;

            // Print the figure based on the number of wrong guesses
            displayFigure( numWrongGuesses );
            printf( "\n" );
            if ( numWrongGuesses == NUM_GUESSES ) {
                break;
            }

            // Print the display word
            displayWord( wordToDisplay );
            printf( "\n");

            // Print the remaining letters to guess
            printf( "Remaining letters:" );
            for ( int i = 0; i < strlen( letters ); i++ ) {
                if ( letters[i] != ' ' ) {
                    printf( " %c", letters[ i ] );
                }
            }
            printf( "\n" );

            // Initialize for fencepost
            bool validIn = true;
            char in[WORD_LENGTH];
            int matches;

            // Prompt for input
            printf( "\nletter> " );

            // Check for garbage input. User must enter a single lowercase letter.
            matches = scanf( "%s", in );
            if ( matches == EOF ) {
                return EXIT_SUCCESS;
            }
            if ( strlen( in ) != 1 ) {
                validIn = false;
            } else if ( in[0] < 'a' || in[0] > 'z' ) {
                validIn = false;
            } else {
                // Check if the letter has already been guessed
                bool notGuessed = false;
                for ( int i = 0; i < strlen( letters ); i++ ) {
                    if ( letters[i] == in[0] ) {
                        notGuessed = true;
                    }
                }
                validIn = notGuessed;
            }

            // Reprompt for input until user enters something valid
            while ( !validIn ) {
                printf( "\nInvalid letter\n" );
                // Prompt for input
                printf( "\nletter> " );

                // Check for garbage input. User must enter a single lowercase letter.
                matches = scanf( "%s", in );
                if ( matches == EOF ) {
                    return EXIT_SUCCESS;
                }

                if ( strlen( in ) != 1 ) {
                    validIn = false;
                } else if ( in[0] < 'a' || in[0] > 'z' ) {
                    validIn = false;
                } else {
                    // Check if the letter has already been guessed
                    bool notGuessed = false;
                    for ( int i = 0; i < strlen( letters ); i++ ) {
                        if ( letters[i] == in[0] ) {
                            notGuessed = true;
                        }
                    }
                    validIn = notGuessed;
                }
            }

            // For a valid input, check the actual word array. Loop through each
            // element in the array. If a given index contains the guessed letter,
            // go to the display word array and swap out the underscore with the
            // letter at that index and increment the correct guess counter.
            // Set a boolean flag so that the wrong guesses counter doesn't increment.
            // Remove the guessed letter from the letters array. Increment the
            // guessed letter counter. If the player has guessed all the letters, set
            // win flag and break
            for ( int i = 0; i < strlen( actualWord ); i++ ) {
                if ( in[0] == actualWord[i] ) {
                    numLettersGuessed++;
                    correctGuess = true;
                    wordToDisplay[i] = in[0];
                }
            }

            // Remove the letter from the list of letters left to guess
            for ( int i = 0; i < strlen( letters ); i++ ) {
                if ( letters[i] == in[0] ) {
                    letters[i] = ' ';
                    break;
                }
            }

            if ( numLettersGuessed == numLettersToGuess ) {
                playerHasWon = true;
                break;
            }

            if ( !correctGuess ) {
                numWrongGuesses++;
            }

        } while (true);

        // Check if the player has won or lost and output proper message
        if ( playerHasWon ) {
            printf( "\n" );
            displayWord( wordToDisplay );
            printf( "\nYou win!\n" );
        } else {
            printf( "You lose!\nWord was %s\n", actualWord );
        }

        // Ask the user if they want to play again. y or Y indicates yes,
        // anything else or EOF means no
        printf( "\nPlay again(y,n)> " );
        char playerResponse[NUM_WORDS * 2];
        int matches = scanf( "%s", playerResponse );
        if ( matches == EOF ) {
            playAgain = false;
            return EXIT_SUCCESS;
        } else if ( playerResponse[0] == 'y' || playerResponse[0] == 'Y' ) {
            playAgain = true;
        } else {
            playAgain = false;
        }

    }

    return EXIT_SUCCESS;

    // Error handling for command line arguments
    commandLineArgError:
        fprintf( stderr, "usage: hangman <word-file> [seed]\n" );
        return EXIT_FAILURE;
}
