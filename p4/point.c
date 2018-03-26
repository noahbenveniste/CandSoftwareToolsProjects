#include "point.h"

Point *parsePoint()
{
    // Assume that a valid "add" command is read in; initialize the Point struct
    int matches; // Used to check if a scanned token matches a format specifier
    
    // First, check that the name token is max 20 characters
    char buffer[ NAME_LEN * 2 ];
    scanf( "%s", buffer );
    
    if ( strlen( buffer ) > NAME_LEN ) {
        return NULL;
    }
    
    // Check that the latitude is within the valid range (defined in point.h)
    double latitude, longitude;
    matches = scanf( "%lf", &latitude );
    if ( matches != 1 ) {
        return NULL;
    } else if ( latitude < MIN_LAT || latitude > MAX_LAT ) {
        return NULL;
    }
    
    // Check that the longitude is within the valid range (defined in point.h)
    matches = scanf( "%lf", &longitude );
    if ( matches != 1 ) {
        return NULL;
    } else if ( longitude < MIN_LAT || longitude > MAX_LAT ) {
        return NULL;
    }
    
    // Check that the description text is within the valid range (defined in point.h)
    // and cointains no newlines or tabs. Read up until END OF LINE
    char descBuffer[ DESC_LEN * 4 ];
    scanf( " %2000[^\n\t]", descBuffer );
    
    if ( strlen( descBuffer ) > DESC_LEN ) {
        return NULL;
    }
    
    /*
    int i = 0;
    char curr = getc(stdin);
    if ( curr == '\n' || curr == '\t' ) {
        return NULL;
    }
    
    // Skip leading whitespace
    while ( curr == ' ' ) {
        curr = getc(stdin);
    }
    descBuffer[ i ] = curr;
    
    // TODO: may need to add additional checks that make sure the description has no
    // newlines or tabs (except a newline at the end)
    while ( curr != '\n' ) {
        i++;
        curr = getc(stdin);
        if ( i > DESC_LEN ) {
            return NULL;
        } else if ( curr == '\t' ) {
            return NULL;
        } else {
            descBuffer[i] = curr;
        }
    }
    descBuffer[i] = '\0'; // Manually add the null terminator at the end
    */
    
    // printf( "%s\n", descBuffer );
    
    // Need to dynamically allocate memory for the description (add 1 for the null terminator)
    char *description = ( char * )malloc( strlen( descBuffer ) + 1 );
    strcpy( description, descBuffer );
    description[ strlen( descBuffer ) ] = '\0';
    
    // printf( "%s, %d\n", description, ( int ) strlen( description ) );
    
    // Once everything is read in and valid, the size of all the fields are known so the Point
    // Struct itself can be dynamically allocated and its fields set
    Point *p = ( Point * )malloc( sizeof( Point ) );
    
    // Copy over the name from the buffer string into the dynamically allocated Point
    // Since p is a pointer to a struct, need to use -> syntax to access and modify fields
    strncpy( p->name, buffer, sizeof( p->name ) - 1 ); // Additional buffer overflow guard
    p->name[ sizeof( p->name ) - 1 ] = '\0'; // Add null terminator manually
    
    // Create a Coords struct and set that field in the Point
    p->location.lat = latitude;
    p->location.lon = longitude;
    
    // Since we already dynamically allocated the description, just set the field in the Point
    p->desc = description;
    
    // Return a pointer to the dynamically allocated Point
    return p;
}

void freePoint( Point *pt )
{
    // Free the memory associated with the description for the Point
    free( pt->desc );
    
    // Free the Point itself
    free( pt );
}

void reportPoint( Point const *pt, Coords const *ref )
{
    printf( "%s (%.1lf miles)\n  %s\n", pt->name, globalDistance( &(pt->location), ref ), pt->desc );
}

double globalDistance( Coords const *c1, Coords const *c2)
{
    // Get the values from the structs
    double lat1 = c1->lat, lon1 = c1->lon, lat2 = c2->lat, lon2 = c2->lon;
    
    /* The following code is taken from the code provided by exercise 13 */
    
    // OK, pretend the center of the earth is at the origin, turn these
    // two locations into vectors pointing from the origin.
    // This could be simplified.
    double v1[] = { cos( lon1 * DEG_TO_RAD ) * cos( lat1 * DEG_TO_RAD ),
                  sin( lon1 * DEG_TO_RAD ) * cos( lat1 * DEG_TO_RAD ),
                  sin( lat1 * DEG_TO_RAD ) };

    double v2[] = { cos( lon2 * DEG_TO_RAD ) * cos( lat2 * DEG_TO_RAD ),
                  sin( lon2 * DEG_TO_RAD ) * cos( lat2 * DEG_TO_RAD ),
                  sin( lat2 * DEG_TO_RAD ) };

    // Dot product these two vectors.
    double dp = 0.0;
    for ( int i = 0; i < sizeof( v1 ) / sizeof( v1[ 0 ] ); i++ )
    dp += v1[ i ] * v2[ i ];

    // Compute the angle between the vectors based on the dot product.
    double angle = acos( dp );

    // Return distance based on the radius of the earth.
    return EARTH_RADIUS * angle;
}

/**
 * Used for testing and debugging the Point struct
 */
int main()
{
    Coords currLocation = { 35.772325, -78.673581 };
    Point *pt;
    
    // Test 1, valid input
    pt = parsePoint();
    reportPoint( pt, &currLocation );
    freePoint( pt );
}