#include <ctype.h>
#include "pointlist.h"

/** The user's current location */
static Coords currentLocation;

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
 *
 * @param pt a pointer to the Point struct being queried for being in range of the user
 * @param data the distance range that the user would like to report points being within
 *
 * @return true if the Point that pt points to is within range of the
 */
static bool nearbyHelper( Point const *pt, void *data )
{
    // In this case, data is a double corresponding to the distance range
    // the user wants. Cast the void pointer to a pointer to a double
    double *range = ( double * ) data;

    // Calculate the Point's distance from the user's current location. If it's within
    // range, return true
    double distance = globalDistance( &( pt->location ), &currentLocation );

    return distance <= *range;
}

/**
 * Used to print Points whose descriptions contain a specified word
 */
static bool matchHelper( Point const *pt, void *data )
{
    // In this case, data is a String corresponding to the word to search for.
    // Cast the void data pointer to a char pointer
    char *str = ( char * ) data;

    // Get the Point's description, copy it into a separate array
    char descCpy[ strlen( pt->desc ) + 1 ];
    strncpy( descCpy, pt->desc, strlen( pt->desc ) );
    descCpy[ strlen( pt->desc ) + 1 ] = '\0';

    // Go through the copy of the description, make everything lowercase and
    // remove all punctuation, dashes, etc (replace them with spaces)
    for ( int i = 0; i < strlen( descCpy ); i++ ) {
        // If the current char isn't a number or letter, replace it with a space
        if ( isalnum( descCpy[ i ] ) == 0 ) {
            descCpy[ i ] = ' ';
        } else if ( islower( descCpy[ i ] ) == 0 ) {
            // If the current char is an uppercase letter, make it lowercase
            descCpy[ i ] = tolower( descCpy [ i ] );
        }
    }

    // Use strtok to tokenize on whitespace, then loop through the tokens
    // and use strcmp to look for the word.
    const char delim[ 2 ] = " "; // Delimiter string containing space and null terminator
    char *token = strtok( descCpy, delim ); // Get the first token

    // int tokenCount = 1;

    // printf( "Token number %d: %s\n", tokenCount, token );

    while ( token != NULL ) {
        // Clear leading and trailing whitespace from token. Get number of non spaces
        int count = 0;
        for ( int i = 0; i < strlen( token ) - 1; i++ ) {
            if ( token[ i ] != ' ' ) {
                count++;
            }
        }

        // Make an array big enough for the alphanum chars, plus null
        char buffer[ count + 1 ];

        // Loop through the token string and copy over all alphanum characters
        int idx = 0;
        for ( int i = 0; i < strlen( token ); i++ ) {
            if ( token[ i ] != ' ' ) {
                buffer[ idx ] = token[ i ];
                idx++;
            }
        }
        buffer[ count + 1 ] = '\0';

        // printf( "Token number %d cleaned: %s\n\n", tokenCount, buffer );


        if ( strcmp( buffer, str ) == 0 ) {
            return true;
        }
        token = strtok( NULL, delim );
        // tokenCount++;
        // printf( "Token number %d: %s\n", tokenCount, token );
    }

    // If no match was found
    return false;
}

/**
 * Main function; handles primary program flow; prompts for user input etc
 *
 * @return 0 for success, anything else for failure
 */
int main()
{
    // Initialize the output line counter
    int commandCounter = 1;

    // Initialize the user's current location
    currentLocation.lat = 35.772325;
    currentLocation.lon = -78.673581;

    // Initialize the pointlist
    Pointlist *ptlist = createPointlist();

    // Loop until the user enters the quit command (use do-while )
    do {
        // Print out the command prompt
        printf( "%d> ", commandCounter );

        // Try to consume the first piece of input by the user (indicates the command to run)
        char cmd[100];
        int matches = scanf( "%s", cmd );

        printf( "\n" );

        // If the input isn't a valid command, throw away the rest of the line, print an error
        // message, reprompt user
        if ( matches == 0 ) {
            goto badInput;
        }

        // Check for EOF or quit command
        if ( matches == EOF || strcmp( cmd, "quit" ) == 0 ) {
            freePointlist( ptlist );
            return EXIT_SUCCESS;
        } else if ( strcmp( cmd, "add" ) == 0 ) {
             // If the command is add, call addPoint on the pointlist. If false is returned, print error
             Point *pt = parsePoint();
             bool result = addPoint( ptlist, pt );

             // Check if the point was added successfully or not
             if ( !result ) {
                 goto badInput;
             }

        } else if ( strcmp( cmd, "remove" ) == 0 ) {
            // If the command is remove, call removePoint. If false is returned, print error
            char nameToRemove[100];
            scanf( "%s", nameToRemove );

            if ( strlen( nameToRemove ) > 20 || !removePoint( ptlist, nameToRemove ) ) {
                fprintf( stdout, "Invalid command\n" );
                goto outOfCheck;
            }

        } else if ( strcmp( cmd, "move" ) == 0 ) {
            // If the command is move, check that the coordinates are valid. If they are, change the
            // user's current location. Else, print error
            double lat;
            double lon;
            int matches = scanf( "%lf%lf", &lat, &lon );
            if ( matches != 2 ) {
                goto badInput;
            } else if ( lat < MIN_LAT || lat > MAX_LAT || lon < MIN_LONG || lon > MAX_LONG ) {
                fprintf( stdout, "Invalid command\n" );
                goto outOfCheck;
            } else {
                currentLocation.lat = lat;
                currentLocation.lon = lon;
            }

        } else if ( strcmp( cmd, "list" ) == 0 ) {
            // If the command is list, call listPoints using the listHelper function and NULL as data
            listPoints( ptlist, &currentLocation, listHelper, NULL );

        } else if ( strcmp( cmd, "nearby" ) == 0 ) {
            // If the command is nearby, try to read in the next token as a double, pass this and a pointer
            // to the nearbyHelper function to listPoints
            double range;
            int matches = scanf( "%lf", &range );
            if ( matches != 1 ) {
                fprintf( stdout, "Invalid command\n" );
                goto outOfCheck;
            } else if ( range < 0 ) {
                fprintf( stdout, "Invalid command\n" );
                goto outOfCheck;
            } else {
                listPoints( ptlist, &currentLocation, nearbyHelper, &range );
            }

        } else if ( strcmp( cmd, "match" ) == 0 ) {
            // If the command is match, try to read in the next token as a string, pass this and a pointer
            // to the matchHelper function to listPoints. If the string contains anything other than
            // 20 lowercase letters, error
            char str[ 100 ];
            int matches = scanf( "%s", str );
            if ( matches != 1 ) {
                fprintf( stdout, "Invalid command\n" );
                goto outOfCheck;
            }

            // Check that str is at most 20 letters and only contains lowercase letters
            if ( strlen( str ) > NAME_LEN ) {
                fprintf( stdout, "Invalid command\n" );
                goto outOfCheck;
            }

            for ( int i = 0; i < strlen( str ); i++ ) {
                // If the current char isn't a lowercase letter
                if ( islower( str[ i ] ) == 0 ) {
                    fprintf( stdout, "Invalid command\n" );
                    goto outOfCheck;
                }
            }
            listPoints( ptlist, &currentLocation, matchHelper, str );

        } else if ( strcmp( cmd, "help" ) == 0 ) {
            // If the command is help, print the help string
            printf( "add <name> <latitude> <longitude> <description>\nremove <name>\nmove <latitude> <longitude>\nlist\nnearby <distance>\nmatch <word>\nhelp\nquit\n" );
        } else {
            badInput:
            fprintf( stdout, "Invalid command\n");

            // Throw away the rest of the input line
            int c = getc(stdin);
            while ( c != '\n' ) {
                c = getc( stdin );
            }

        }
        outOfCheck:

        // Increment command counter
        commandCounter++;

    } while ( true );

}