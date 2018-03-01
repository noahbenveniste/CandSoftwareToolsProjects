/** Defines data and behavior related to reading in the
  * provided text file of words into the program as well
  * as handling bad input.
  * @file wordlist.h
  * @author Noah Benveniste
  */
#define NUM_WORDS 50
#define WORD_LENGTH 20

/*
A statically allocated array to store the words read 
in from the file
*/
extern char words[NUM_WORDS][WORD_LENGTH + 1];

/** Keeps track of the number of words read in from the file */
extern int wordCount;

/** Function that given a file of words, generates an array
  * for the program to take words from for game play. If the
  * file contains too many words, any of the words are too
  * long or any of the words contain anything other than lower
  * case letters, the program exits.
  *
  * @param fileName a string pointer to the name of the file
  * containing the word list to be read in.
  */
void readWords( char const *filename );
