#include "pointlist.h"

/** The user's current location */
static Coords const *currentLocation;

Pointlist *createPointlist()
{
    // Dynamically allocate an initialized Pointlist
    Pointlist *ptlist = ( Pointlist * ) malloc( sizeof( Pointlist ) );

    // Set the count (size) and capacity
    ptlist->count = 0;
    ptlist->cap = 5; // Can initially store 5 Points before a resize is needed

    // Malloc space fo the list
    ptlist->list = ( Point ** ) malloc( sizeof( Point ) * ptlist->cap );

    return ptlist;

}

void freePointlist( Pointlist *ptlist )
{
    Point **currList = ptlist->list;
    // Loop through the array and free all Point objects declared
    for ( int i = 0; i < ptlist->count; i++ ) {
        freePoint( currList[ i ] );
    }

    // Free the array itself
    free( ptlist->list );

    // Free the Pointlist itself
    free( ptlist );

}

/**
 * Helper function used to reallocate a larger array for the Pointlist
 * and copy over the contents from the old array to the new one, as well
 * as free memory used by the old array.
 *
 * @param ptlist
 */
void ensureCap( Pointlist *ptlist )
{
    // Double the Pointlist's capacity
    ptlist->cap *= 2;

    // Call realloc to allocate new memory, copy over the contents of the
    // old array to the new one, and then free the old memory
    ptlist->list = ( Point ** ) realloc( ptlist->list, sizeof( Point ) * ptlist->cap );
}

bool addPoint( Pointlist *ptlist, Point *pt )
{
    // First, check that the list hasn't yet reached capacity. If it has,
    // call ensureCap
    if ( ptlist->count == ptlist->cap ) {
        ensureCap( ptlist );
    }

    // Next, check that the list does not already contain a Point with the
    // same name. If it does, return false
    for ( int i = 0; i < ptlist->count; i++ ) {
        Point *curr = ptlist->list[ i ];

        // If a point with the same name is already on the list
        if ( strcmp( curr->name, pt->name ) == 0 ) {
            // Free the point if its not being added to avoid memory leaks!
            freePoint( pt );
            return false;
        }

    }

    // If the list does not already contain a Point with the same name,
    // add it to the list
    ptlist->list[ ptlist->count ] = pt;

    // Don't forget to increment count
    ptlist->count++;

    // Return true since the element was added successfully
    return true;

}

bool removePoint( Pointlist *ptlist, char const *name )
{
    // Search for the Point with the given name. If it isn't found, return false
    for ( int i = 0; i < ptlist->count; i++ ) {
        Point *curr = ptlist->list[ i ];

        // Point with the name is found
        if ( strcmp( curr->name, name ) == 0 ) {
            // If the Point is found, free the Point
            freePoint( ptlist->list[ i ] );

            // Perform left shift
            for ( int j = i; j < ( ptlist->count ) - 1; j++ ) {
                ptlist->list[ j ] = ptlist->list[ j + 1 ];
            }

            // Make sure to null the value at the old end of the list to prevent memory leaks
            ptlist->list[ ( ptlist->count ) - 1 ] = NULL;

            // Decrement the list's size
            ptlist->count--;

            // Return true
            return true;
        }

    }
    return false; // The name wasn't found

    // If the Point is found, free the Point

    // Perform any necessary shifting of the list (removing from the end of the list
    // is a special case)

    // Make sure to null the value at the old end of the list to prevent memory leaks

    // Decrement the list's size

}


/**
 * Helper function used by listPoints when sorting the pointlist by
 * distance to the user's current location
 *
 * @param p1
 * @param p2
 *
 * @return an int < 0 if the element p1 points to comes before the one p2 points to
 *         exactly 0 if the elements p1 and p2 point to are equivalent
 *         an int > 0 if the element p1 points to comes after the one p2 points to
 */
static int compareTo( const void *p1, const void *p2 )
{
    // The pointers this function takes are pointers to pointers to Point structs;
    // cast them accordingly
    const Point **point1 = ( const Point ** ) p1, **point2 = ( const Point ** ) p2;

    // Using the globalDistance function, calculate each point's distance to the user's
    // current location (get the coord struct from the point and use the currentLocation coord)
    double d1 = globalDistance( &( *point1 )->location, currentLocation );
    double d2 = globalDistance( &( *point2 )->location, currentLocation );

    // Determine which point is closest to the user
    if ( d1 < d2 ) {
        return -1;
    } else if ( d1 > d2 ) {
        return 1;
    } else {
        // If the points are equidistant, return based on alphabetical order of the name of the Point
        return strcmp( ( *point1 )->name, ( *point2 )->name );
    }

}

void listPoints( Pointlist *ptlist, Coords const *ref, bool (*test) ( Point const *pt, void *data ), void *data )
{
    // Used by the comparator function to sort Points by distance from the user
    currentLocation = ref;

    // Sort the list using qsort and the comparator function defined above
    qsort( ptlist->list, ptlist->count, sizeof( Point * ), compareTo );

    // Once the list is sorted, loop through the list, passing each Point and data to the test function
    for ( int i = 0; i < ptlist->count; i++ ) {
        // If the test function returns true, report the point
        if ( test( ptlist->list[ i ], data ) ) {
            reportPoint( ptlist->list[ i ], currentLocation );
        }

    }

}

/**
 * Used for debugging
 *
int main()
{
    // Used to simulate the current location struct being passed by main in attractions
    const Coords currLocation = { 35.772325, -78.673581 };

    // Initialize the pointlist
    Pointlist *ptlist = createPointlist();
    printf( "count: %d\n", ptlist->count );
    printf( "cap: %d\n", ptlist->cap );

    // Add a point
    Point *pt1 = parsePoint();
    printf( "\n" );
    reportPoint ( pt1, &currLocation );
    if ( addPoint( ptlist, pt1 ) ) {
        printf( "Point 1 added successfully!\n" );
        printf( "count: %d\n", ptlist->count );
        printf( "cap: %d\n", ptlist->cap );
    }

    // Add a second point
    Point *pt2 = parsePoint();
    printf( "\n" );
    reportPoint ( pt2, &currLocation );
    if ( addPoint( ptlist, pt2 ) ) {
        printf( "Point 2 added successfully!\n" );
        printf( "count: %d\n", ptlist->count );
        printf( "cap: %d\n", ptlist->cap );
    }

    // Add a third point
    Point *pt3 = parsePoint();
    printf( "\n" );
    reportPoint ( pt3, &currLocation );
    if ( addPoint( ptlist, pt3 ) ) {
        printf( "Point 3 added successfully!\n" );
        printf( "count: %d\n", ptlist->count );
        printf( "cap: %d\n", ptlist->cap );
    }

    // Add a fourth point
    Point *pt4 = parsePoint();
    printf( "\n" );
    reportPoint ( pt4, &currLocation );
    if ( addPoint( ptlist, pt4 ) ) {
        printf( "Point 4 added successfully!\n" );
        printf( "count: %d\n", ptlist->count );
        printf( "cap: %d\n", ptlist->cap );
    }

    // Add a fifth poin
    Point *pt5 = parsePoint();
    printf( "\n" );
    reportPoint ( pt5, &currLocation );
    if ( addPoint( ptlist, pt5 ) ) {
        printf( "Point 5 added successfully!\n" );
        printf( "count: %d\n", ptlist->count );
        printf( "cap: %d\n", ptlist->cap );
    }

    // Add a sixth point
    Point *pt6 = parsePoint();
    printf( "\n" );
    reportPoint ( pt6, &currLocation );
    if ( addPoint( ptlist, pt6 ) ) {
        printf( "Point 6 added successfully!\n" );
        printf( "count: %d\n", ptlist->count );
        printf( "cap: %d\n", ptlist->cap );
    }

    // Try adding a duplicate point
    Point *dup = parsePoint();
    printf( "\n" );
    reportPoint ( dup, &currLocation );
    if ( !addPoint( ptlist, dup ) ) {
        printf( "No duplicates allowed!\n" );
        printf( "count: %d\n", ptlist->count );
        printf( "cap: %d\n", ptlist->cap );
    }

    // Add a seventh point
    Point *pt7 = parsePoint();
    printf( "\n" );
    reportPoint ( pt7, &currLocation );
    if ( addPoint( ptlist, pt7 ) ) {
        printf( "Point 7 added successfully!\n" );
        printf( "count: %d\n", ptlist->count );
        printf( "cap: %d\n", ptlist->cap );
    }

    // Output the list in sorted order
    printf( "\n" );
    listPoints( ptlist, &currLocation, listHelper, NULL );

    // Remove a point from the middle of the list

    // Remove a point from the front of the list

    // Remove a point from the end of the list

    // Add another point

    // Output the list again, re-sorting it

    // Free the list
    freePointlist( ptlist );
    return 0;
}
*/