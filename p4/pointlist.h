#include <stdlib.h>
#include <stdbool.h>
#include "point.h"

#ifndef POINTLIST_H
#define POINTLIST_H

/** */
typedef struct {

    /** The number of Point pointers in the Pointlist */
    int count;

    /** The current capacity of the Pointlist */
    int cap;

    /** Pointer to an array of pointers to Point objects */
    Point **list;
} Pointlist;

/**
 * Initializes a pointlist
 *
 * @return a pointer to a malloc'd pointlist
 */
Pointlist *createPointlist();

/**
 * Frees a malloc'd pointlist
 *
 * @param ptlist the pointlist to free
 */
void freePointlist( Pointlist *ptlist );

/**
 * Adds a point to the given pointlist
 *
 * @param ptlist the pointlist to add to
 * @param pt the point to add
 */
bool addPoint( Pointlist *ptlist, Point *pt );

/**
 * Removes a point with a specified name from the pointlist
 *
 * @param ptlist the point to remove from
 * @param name the name of the point to remove
 *
 * @return true if the point was removed, false if it wasn't in the list
 */
bool removePoint( Pointlist *ptlist, char const *name );

/**
 * Lists the points in the pointlist based on a passed test function
 *
 * @param ptlist the pointlist to print
 * @param ref the user's current location
 * @param test pointer to a function that determines which points to print
 * @param data some piece of data used by test to determine which points to print
 */
void listPoints( Pointlist *ptlist, Coords const *ref, bool (*test) ( Point const *pt, void *data ), void *data );

#endif