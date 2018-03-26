#include "point.h"
#include "pointlist.h"

/**
 * Used to print all Points in the Pointlist
 *
 * @param pt a pointer to the Point struct to check for printing
 * @param data always NULL in this case since this function always returns true
 *
 * @return true (always)
 */
static bool listHelper( Point const *pt, void *data )
{
    return true;
}

/**
 * Used to print Points that are within a specified range of the user
 */
static bool nearbyHelper( Point const *pt, void *data )
{
    // In this case, data is a double corresponding to the distance range
    // the user wants. Cast the void pointer to a double
    
    // Calculate the Point's distance from the user's current location. If it's within
    // range, return true
    
    
    return false;
}

/** 
 * Used to print Points whose descriptions contain a specified word
 */
static bool matchHelper( Point const *pt, void *data )
{
    // In this case, data is a String corresponding to the word to search for.
    // Cast the void data pointer to a char pointer
    
    // Use strstr to search pt's description string for the string that data
    // corresponds to. If strstr returns anything but null, return true
    
}

/**
 *
 */
int main()
{
    // Initialize the output line counter
    int commandCounter = 1;
    
    // Initialize the pointlist
    
    // Loop until the user enters the quit command (use do-while )
    
    // Try to consume the first piece of input by the user (indicates the command to run)
    
    // If the input isn't a valid command, throw away the rest of the line, print an error
    // message, reprompt user
    
    // If the command is add, call addPoint on the pointlist. If false is returned, print error
    
    // If the command is remove, call removePoint. If false is returned, print error
    
    // If the command is move, check that the coordinates are valid. If they are, change the
    // user's current location. Else, print error
    
    // If the command is list, call listPoints using the listHelper function and NULL as data
    
    // If the command is nearby, try to read in the next token as a double, pass this and a pointer
    // to the nearbyHelper function to listPoints
    
    // If the command is match, try to read in the next token as a string, pass this and a pointer
    // to the matchHelper function to listPoints
    
    // If the command is help, print the help string
    printf( "add <name> <latitude> <longitude> <description>\nremove <name>\nmove <latitude> <longitude>\nlist\nnearby <distance>\nmatch <word>\nhelp\nquit\n" );
    
    // If the command is quit or EOF is reached, free the pointlist and then exit successfully
    
}