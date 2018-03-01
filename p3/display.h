/** Defines behavior for displaying game state information
  * between turns of the game.
  *
  * @file display.h
  * @author Noah Benveniste
  */
  
/** Prints a given word to the console with spaces between
  * each letter.
  *
  * @param word the word to be printed to the console
  */
void displayWord(char word[]);

/** Displays the hangman figure with the specified number
  * of body parts drawn in.
  *
  * @param numberOfParts the number of body parts that the
  * figure has when it is printed
  */
void displayFigure(int numberOfParts);
